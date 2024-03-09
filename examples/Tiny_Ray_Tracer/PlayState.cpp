#include <iomanip>

#include "PlayState.h"
#include "Data.h"

// TODO: Figure out where to put this
uint32_t rgb888ToRgb565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

PlayState::PlayState(const std::shared_ptr<FiniteStateMachine>& finiteStateMachine,
                     uint16_t screenWidth,
                     uint16_t screenHeight)
   : mFSM(finiteStateMachine)
   , mScreenWidth(screenWidth)
   , mScreenHeight(screenHeight)
   , mFileParser(nullptr)
   , mSceneDesc(nullptr)
   , mScene(nullptr)
{

}

void PlayState::enter()
{
   mFileParser.reset(new FileParser(sceneDescriptions[0]));
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

   //mAmoled->pushColors(0, 0, mScreenWidth, mScreenHeight, (uint16_t *)mImageRenderingSprite.getPointer());
}

void PlayState::update()
{
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

         //mImageRenderingSprite.drawPixel(mSample.x, mSample.y, colour);

         //uint16_t* spritePtr = (uint16_t*)mImageRenderingSprite.getPointer();
         //uint16_t* pixelPtr = spritePtr + (mSample.y * mScreenWidth + mSample.x);
         //mAmoled->setAddrWindow(mSample.x, mSample.y, mSample.x, mSample.y);
         //mAmoled->pushColors(pixelPtr, 1);
      }
   }
}

void PlayState::exit()
{

}
