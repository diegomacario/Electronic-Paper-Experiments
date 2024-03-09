#include <iomanip>

#include "PlayState.h"
#include "MenuState.h"
#include "Data.h"

// TODO: Figure out where to put this
uint32_t rgb888ToRgb565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

PlayState::PlayState(const std::shared_ptr<FiniteStateMachine>& finiteStateMachine,
                     LilyGo_Class* amoled,
                     TFT_eSPI& tft,
                     uint16_t screenWidth,
                     uint16_t screenHeight)
   : mFSM(finiteStateMachine)
   , mAmoled(amoled)
   , mScreenWidth(screenWidth)
   , mScreenHeight(screenHeight)
   , mImageRenderingSprite(&tft)
   , mRayTracingLabelSprite(&tft)
   , mRayTracingLabelBackgroundSprite(&tft)
   , mRayTracingLabelMixedSprite(&tft)
   , mPercentageProgressLabelSprite(&tft)
   , mPercentageProgressLabelBackgroundSprite(&tft)
   , mPercentageProgressLabelMixedSprite(&tft)
   , mProgressBarSprite(&tft)
   , mProgressBarBackgroundSprite(&tft)
   , mProgressBarMixedSprite(&tft)
   , mFileParser(nullptr)
   , mSceneDesc(nullptr)
   , mScene(nullptr)
   , mRayTracingSpriteSettings(3, 8, 6, "Ray-tracing...")
   , mNumDots(0)
   , mLastTimeRayTracingSpriteWasUpdated(0)
   , mRayTracingLabelBackgroundSpriteChanged(false)
   , mPercentageProgressSpriteSettings(3, 8, 6, "100.0%")
   , mProgressBarWidth(536)
   , mProgressBarHeight(10)
   , mProgressBarXPosition(0)
   , mProgressBarYPosition(240 - mProgressBarHeight)
   , mProgressBarFillableWidth(mProgressBarWidth)
   , mProgressBarFillableHeight(mProgressBarHeight)
   , mPrevProgressWidth(0)
   , mDoOnce(true)
   , mCancelRenderButtonPin(1)
   , mCancelRenderButtonState(LOW)
   , mLastCancelRenderButtonState(LOW)
   , mLastCancelRenderButtonDebounceTime(0)
   , mCancelRenderButtonDebounceDelay(50)
{

}

void PlayState::enter()
{
   mImageRenderingSprite.createSprite(mScreenWidth, mScreenHeight);
   mImageRenderingSprite.fillSprite(TFT_BLACK);

   mRayTracingLabelSprite.createSprite(mRayTracingSpriteSettings.spriteWidth, mRayTracingSpriteSettings.spriteHeight);
   mRayTracingLabelSprite.fillSprite(TFT_BLACK);
   mRayTracingLabelSprite.setTextColor(TFT_WHITE);
   mRayTracingLabelSprite.setTextSize(mRayTracingSpriteSettings.textSize);
   mRayTracingLabelSprite.setTextFont(1);
   mRayTracingLabelSprite.drawString("Ray-tracing", 0, 0);
   mRayTracingLabelSprite.setTextDatum(TL_DATUM);

   mRayTracingLabelBackgroundSprite.createSprite(mRayTracingSpriteSettings.spriteWidth, mRayTracingSpriteSettings.spriteHeight);
   mRayTracingLabelBackgroundSprite.fillSprite(TFT_BLACK);

   mRayTracingLabelMixedSprite.createSprite(mRayTracingSpriteSettings.spriteWidth, mRayTracingSpriteSettings.spriteHeight);
   mRayTracingLabelMixedSprite.fillSprite(TFT_BLACK);

   mPercentageProgressLabelSprite.createSprite(mPercentageProgressSpriteSettings.spriteWidth, mPercentageProgressSpriteSettings.spriteHeight);
   mPercentageProgressLabelSprite.fillSprite(TFT_BLACK);
   mPercentageProgressLabelSprite.setTextColor(TFT_WHITE);
   mPercentageProgressLabelSprite.setTextSize(mPercentageProgressSpriteSettings.textSize);
   mPercentageProgressLabelSprite.setTextFont(1);
   mPercentageProgressLabelSprite.drawString("0.0%", mPercentageProgressSpriteSettings.spriteWidth, 0);
   mPercentageProgressLabelSprite.setTextDatum(TR_DATUM);

   mPercentageProgressLabelBackgroundSprite.createSprite(mPercentageProgressSpriteSettings.spriteWidth, mPercentageProgressSpriteSettings.spriteHeight);
   mPercentageProgressLabelBackgroundSprite.fillSprite(TFT_BLACK);

   mPercentageProgressLabelMixedSprite.createSprite(mPercentageProgressSpriteSettings.spriteWidth, mPercentageProgressSpriteSettings.spriteHeight);
   mPercentageProgressLabelMixedSprite.fillSprite(TFT_BLACK);

   mProgressBarSprite.createSprite(mProgressBarWidth, mProgressBarHeight);
   mProgressBarSprite.fillSprite(TFT_BLACK);

   mProgressBarBackgroundSprite.createSprite(mProgressBarWidth, mProgressBarHeight);
   mProgressBarBackgroundSprite.fillSprite(TFT_BLACK);

   mProgressBarMixedSprite.createSprite(mProgressBarWidth, mProgressBarHeight);
   mProgressBarMixedSprite.fillSprite(TFT_BLACK);

   int32_t sceneDescriptionIndex = std::static_pointer_cast<MenuState>(mFSM->getPreviousState())->getCurrentCellIndex();
   mFileParser.reset(new FileParser(sceneDescriptions[sceneDescriptionIndex]));
   mFileParser->readFile(mSceneDesc, mScene);

   mSampleGenerator = RandomSampleGenerator(mSceneDesc->getWidth(), mSceneDesc->getHeight());

   mRayGenerator = RayGenerator(mSceneDesc->getWidth(),
                                mSceneDesc->getHeight(),
                                mSceneDesc->getEye(),
                                mSceneDesc->getCenter(),
                                mSceneDesc->getUpVec(),
                                mSceneDesc->getFovy());

   mRay.origin = mSceneDesc->getEye();
   mRay.direction = Vector(0, 0, 0);

   mNumDots = 0;
   mLastTimeRayTracingSpriteWasUpdated = 0;
   mPrevProgressWidth = 0;
   mDoOnce = true;

   mCancelRenderButtonState = LOW;
   mLastCancelRenderButtonState = LOW;
   mLastCancelRenderButtonDebounceTime = 0;

   pinMode(mCancelRenderButtonPin, INPUT_PULLDOWN);

   mAmoled->pushColors(0, 0, mScreenWidth, mScreenHeight, (uint16_t *)mImageRenderingSprite.getPointer());
}

void PlayState::update()
{
   bool cancelRenderButtonIsPressed = checkCancelRenderButton();
   if (cancelRenderButtonIsPressed) {
      mFSM->changeState("menu");
      return;
   }

   if (mSampleGenerator.sampleIsAvailable())
   {
      mSampleGenerator.generateSample(mSample);
      mRayGenerator.generateRay(mSample, mRay);

      // If the current ray intersects an object, we calculate the lighting at the intersection point and store the colour
      // If not, the current pixel remains black
      if (mScene->findNearestIntersection(mRay, &mIntersection))
      {
         Colour pixelColour = mScene->calculateLightingAtIntersection(mSceneDesc->getEye(), &mIntersection);

         uint8_t r = static_cast<uint8_t>(std::min(255 * pixelColour.r, 255.0f));
         uint8_t g = static_cast<uint8_t>(std::min(255 * pixelColour.g, 255.0f));
         uint8_t b = static_cast<uint8_t>(std::min(255 * pixelColour.b, 255.0f));
         uint32_t colour = rgb888ToRgb565(r, g, b);

         mImageRenderingSprite.drawPixel(mSample.x, mSample.y, colour);

         if ((mSample.x < mRayTracingSpriteSettings.spriteWidth) && (mSample.y < mRayTracingSpriteSettings.spriteHeight)) {
            // We rendered a pixel that's behind mRayTracingLabelSprite
            // Let's save it in mRayTracingLabelBackgroundSprite
            mRayTracingLabelBackgroundSprite.drawPixel(mSample.x, mSample.y, colour);
            mRayTracingLabelBackgroundSpriteChanged = true;
         }

         int32_t percentageProgressLabelXPos = mScreenWidth - mPercentageProgressSpriteSettings.spriteWidth;
         int32_t percentageProgressLabelYPos = mScreenHeight - mPercentageProgressSpriteSettings.spriteHeight;
         if ((mSample.x >= percentageProgressLabelXPos) && (mSample.y >= percentageProgressLabelYPos)) {
            // We rendered a pixel that's behind mPercentageProgressLabelSprite
            // Let's save it in mPercentageProgressLabelBackgroundSprite
            mPercentageProgressLabelBackgroundSprite.drawPixel(mSample.x - percentageProgressLabelXPos, mSample.y - percentageProgressLabelYPos, colour);
         }

         if ((mSample.x >= mProgressBarXPosition) &&
             (mSample.x < mProgressBarXPosition + mProgressBarWidth) &&
             (mSample.y >= mProgressBarYPosition) &&
             (mSample.y < mProgressBarYPosition + mProgressBarHeight)) {
            // We rendered a pixel that's behind mProgressBarSprite
            // Let's save it in mProgressBarBackgroundSprite
            mProgressBarBackgroundSprite.drawPixel(mSample.x - mProgressBarXPosition, mSample.y - mProgressBarYPosition, colour);
         }

         uint16_t* spritePtr = (uint16_t*)mImageRenderingSprite.getPointer();
         uint16_t* pixelPtr = spritePtr + (mSample.y * mScreenWidth + mSample.x);
         mAmoled->setAddrWindow(mSample.x, mSample.y, mSample.x, mSample.y);
         mAmoled->pushColors(pixelPtr, 1);
      }

      float progress = mSampleGenerator.getProgress();

      updateRayTracingSprite();
      updatePercentageProgressSprite(progress);
      //updateProgressBar(progress);
   }
   else if (mDoOnce) {
      mRayTracingLabelSprite.fillSprite(TFT_BLACK);
      std::string doneString = "Done!";
      mRayTracingLabelSprite.drawString(doneString.c_str(), 0, 0);
      mRayTracingLabelBackgroundSprite.pushToSprite(&mRayTracingLabelMixedSprite, 0, 0);
      mRayTracingLabelSprite.pushToSprite(&mRayTracingLabelMixedSprite, 0, 0, TFT_BLACK);
      mAmoled->pushColors(0, 0, mRayTracingSpriteSettings.spriteWidth, mRayTracingSpriteSettings.spriteHeight, (uint16_t *)mRayTracingLabelMixedSprite.getPointer());

      delay(2000);

      mAmoled->pushColors(0, 0, mScreenWidth, mScreenHeight, (uint16_t *)mImageRenderingSprite.getPointer());
      mDoOnce = false;
   }
}

void PlayState::exit()
{
   mImageRenderingSprite.deleteSprite();
   mRayTracingLabelSprite.deleteSprite();
   mRayTracingLabelBackgroundSprite.deleteSprite();
   mRayTracingLabelMixedSprite.deleteSprite();
   mPercentageProgressLabelSprite.deleteSprite();
   mPercentageProgressLabelBackgroundSprite.deleteSprite();
   mPercentageProgressLabelMixedSprite.deleteSprite();
   mProgressBarSprite.deleteSprite();
   mProgressBarBackgroundSprite.deleteSprite();
   mProgressBarMixedSprite.deleteSprite();
}

bool PlayState::checkCancelRenderButton()
{
   bool cancelRenderButtonIsPressed = false;

   int reading = digitalRead(mCancelRenderButtonPin);

   if (reading != mLastCancelRenderButtonState) {
      // Reset the debouncing timer
      mLastCancelRenderButtonDebounceTime = millis();
   }

   if ((millis() - mLastCancelRenderButtonDebounceTime) > mCancelRenderButtonDebounceDelay) {
      // Whatever the reading is at, it's been there for longer than the debounce delay,
      // so take it as the actual current state

      // If the button state has changed
      if (reading != mCancelRenderButtonState) {
         mCancelRenderButtonState = reading;

         // If the new state of the button is HIGH
         if (mCancelRenderButtonState == HIGH) {
            cancelRenderButtonIsPressed = true;
         }
      }
   }

   mLastCancelRenderButtonState = reading;

   return cancelRenderButtonIsPressed;
}

void PlayState::updateRayTracingSprite() {
    if (millis() > mLastTimeRayTracingSpriteWasUpdated + 1000) {
        mNumDots += 1;
        mNumDots %= 4;
        mRayTracingLabelSprite.fillSprite(TFT_BLACK);
        std::string rayTracingString = "Ray-tracing";
        switch(mNumDots) {
            case 0:
                break;
            case 1:
                rayTracingString += ".";
                break;
            case 2:
                rayTracingString += "..";
                break;
            case 3:
                rayTracingString += "...";
                break;
            default:
                break;
        }
        mRayTracingLabelSprite.drawString(rayTracingString.c_str(), 0, 0);
        mRayTracingLabelBackgroundSprite.pushToSprite(&mRayTracingLabelMixedSprite, 0, 0);
        mRayTracingLabelSprite.pushToSprite(&mRayTracingLabelMixedSprite, 0, 0, TFT_BLACK);
        mAmoled->pushColors(0, 0, mRayTracingSpriteSettings.spriteWidth, mRayTracingSpriteSettings.spriteHeight, (uint16_t *)mRayTracingLabelMixedSprite.getPointer());
        mLastTimeRayTracingSpriteWasUpdated = millis();
        mRayTracingLabelBackgroundSpriteChanged = false;
    } else if (mRayTracingLabelBackgroundSpriteChanged) {
        mRayTracingLabelBackgroundSprite.pushToSprite(&mRayTracingLabelMixedSprite, 0, 0);
        mRayTracingLabelSprite.pushToSprite(&mRayTracingLabelMixedSprite, 0, 0, TFT_BLACK);
        mAmoled->pushColors(0, 0, mRayTracingSpriteSettings.spriteWidth, mRayTracingSpriteSettings.spriteHeight, (uint16_t *)mRayTracingLabelMixedSprite.getPointer());
        mRayTracingLabelBackgroundSpriteChanged = false;
    }
}

void PlayState::updatePercentageProgressSprite(float progress) {
    mPercentageProgressLabelSprite.fillSprite(TFT_BLACK);
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << (progress * 100.0f);
    std::string numberAsString = stream.str();
    numberAsString += "%";
    mPercentageProgressLabelSprite.drawString(numberAsString.c_str(), mPercentageProgressSpriteSettings.spriteWidth, 0);
    mPercentageProgressLabelBackgroundSprite.pushToSprite(&mPercentageProgressLabelMixedSprite, 0, 0);
    mPercentageProgressLabelSprite.pushToSprite(&mPercentageProgressLabelMixedSprite, 0, 0, TFT_BLACK);
    mAmoled->pushColors(mScreenWidth - mPercentageProgressSpriteSettings.spriteWidth,
                        mScreenHeight - mPercentageProgressSpriteSettings.spriteHeight,
                        mPercentageProgressSpriteSettings.spriteWidth,
                        mPercentageProgressSpriteSettings.spriteHeight,
                        (uint16_t *)mPercentageProgressLabelMixedSprite.getPointer());
}

void PlayState::updateProgressBar(float progress) {
    int32_t progressWidth = static_cast<int32_t>(progress * static_cast<float>(mProgressBarFillableWidth));
    if (progressWidth > mPrevProgressWidth) {
        mProgressBarSprite.fillRect(1, 1, progressWidth, mProgressBarFillableHeight, TFT_GREEN);
        mPrevProgressWidth = progressWidth;
    }

    mProgressBarBackgroundSprite.pushToSprite(&mProgressBarMixedSprite, 0, 0);
    mProgressBarSprite.pushToSprite(&mProgressBarMixedSprite, 0, 0, TFT_BLACK);
    mAmoled->pushColors(mProgressBarXPosition, mProgressBarYPosition, mProgressBarWidth, mProgressBarHeight, (uint16_t *)mProgressBarMixedSprite.getPointer());
}
