#include <iostream>

#include <Arduino.h>
#include "epd_driver.h"
#include "pins.h"

#include "PlayState.h"
#include "Data.h"

// TODO: Figure out where to put this
float sRGBtoLin(float colorChannel) {
   // Send this function a decimal sRGB gamma encoded color value
   // between 0.0 and 1.0, and it returns a linearized value.

   if (colorChannel <= 0.04045f) {
      return colorChannel / 12.92f;
   } else {
      return pow(((colorChannel + 0.055f) / 1.055f), 2.4f);
   }
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
   , mQuadrantIndex(0)
   , mGenerateCoordinatesOfQuadrants(true)
   , mGenerateNoiseOfQuadrants(false)
{
   mImageRenderingFramebuffer = (uint8_t *)heap_caps_malloc(mScreenWidth * mScreenHeight / 2, MALLOC_CAP_SPIRAM);

   if (!mImageRenderingFramebuffer) {
        Serial.println("Memory allocation failed!");
   }

   memset(mImageRenderingFramebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

   mNoiseFramebuffer = (uint8_t *)heap_caps_malloc(mScreenWidth * mScreenHeight / 2, MALLOC_CAP_SPIRAM);

   if (!mNoiseFramebuffer) {
        Serial.println("Memory allocation failed!");
   }
   
   memset(mNoiseFramebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
}

void PlayState::enter()
{
   mFileParser.reset(new FileParser(sceneDescriptions[8]));
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
}

bool done = false;

void PlayState::update()
{
   if (mGenerateCoordinatesOfQuadrants) {
      if (mQuadrantIndex <= 4) {
         if (mQuadrantIndex <= 3) {
            mSampleGenerator.generateCoordinates(mQuadrantIndex);
            ++mQuadrantIndex;
         }
         else {
            mSampleGenerator.shuffleCoordinates();
            mQuadrantIndex = 0;
            mGenerateCoordinatesOfQuadrants = false;
            mGenerateNoiseOfQuadrants = true;
         }

         return;
      }
   } else if (mGenerateNoiseOfQuadrants) {
      if (mQuadrantIndex <= 3) {
         generateNoise(mQuadrantIndex);

         if (mQuadrantIndex == 3) {
            mGenerateNoiseOfQuadrants = false;
         }

         ++mQuadrantIndex;
      }

      return;
   }

   epd_poweron();

   if (done) {
      epd_draw_grayscale_image(epd_full_screen(), mImageRenderingFramebuffer);
      delay(5000);
      epd_clear();
      epd_poweroff();
      return;
   }

   for (int i = 0; i < 960; ++i) {
      if (mSampleGenerator.sampleIsAvailable())
      {
         mSampleGenerator.generateSample(mSample);
         mRayGenerator.generateRay(mSample, mRay);

         // If the current ray intersects an object, we calculate the lighting at the intersection point and store the colour
         // If not, the current pixel remains black
         if (mScene->findNearestIntersection(mRay, &mIntersection))
         // if (true)
         {
            Colour pixelColour = mScene->calculateLightingAtIntersection(mSceneDesc->getEye(), &mIntersection);

            float vR = pixelColour.r;
            float vG = pixelColour.g;
            float vB = pixelColour.b;

            //float Y = (0.2126f * sRGBtoLin(vR) + 0.7152f * sRGBtoLin(vG) + 0.0722f * sRGBtoLin(vB));
            //uint8_t luminance = static_cast<uint8_t>(std::min(255 * Y, 255.0f));
            // uint8_t luminance = 0;
            //epd_draw_pixel(mSample.x, mSample.y, luminance, mImageRenderingFramebuffer);

            float gray = 0.2989f * vR + 0.5870f * vG + 0.1140f * vB;
            uint8_t gray2 = static_cast<uint8_t>(std::min(255.0f * gray, 255.0f));

            //uint8_t gray2 = (uint8_t)((vR + vG + vB) / 3.0f * 255);

            epd_draw_pixel(mSample.x, mSample.y, gray2, mImageRenderingFramebuffer);
         } else {
            //epd_draw_pixel(mSample.x, mSample.y, 0, mImageRenderingFramebuffer);
         }
      } else {
         done = true;
      }
   }

   //Serial.println("Done with row!");

   //epd_draw_grayscale_image(epd_full_screen(), mImageRenderingFramebuffer);
   delay(1000);
   //memset(mImageRenderingFramebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
   epd_clear();
   epd_poweroff();
}

void PlayState::exit()
{

}

void PlayState::generateNoise(int quadrantIndex)
{
   int halfWidth = mScreenWidth / 2;
   int halfHeight = mScreenHeight / 2;

   switch (quadrantIndex) {
   case 0: // Top left
      std::cout << "0 - Generate noise of top left quadrant" << '\n';
      for (int32_t i = 0; i < halfWidth; ++i) {
         for (int32_t j = 0; j < halfHeight; ++j) {
            uint8_t value = random(255);
            epd_draw_pixel(i, j, value, mNoiseFramebuffer);
         }
      }
      break;
   case 1: // Top right
      std::cout << "1 - Generate noise of top right quadrant" << '\n';
      for (int32_t i = halfWidth; i < mScreenWidth; ++i) {
         for (int32_t j = 0; j < halfHeight; ++j) {
            uint8_t value = random(255);
            epd_draw_pixel(i, j, value, mNoiseFramebuffer);
         }
      }
      break;
   case 2: // Bottom left
      std::cout << "2 - Generate noise of bottom left quadrant" << '\n';
      for (int32_t i = 0; i < halfWidth; ++i) {
         for (int32_t j = halfHeight; j < mScreenHeight; ++j) {
            uint8_t value = random(255);
            epd_draw_pixel(i, j, value, mNoiseFramebuffer);
         }
      }
      break;
   case 3: // Bottom right
      std::cout << "3 - Generate noise of bottom right quadrant" << '\n';
      for (int32_t i = halfWidth; i < mScreenWidth; ++i) {
         for (int32_t j = halfHeight; j < mScreenHeight; ++j) {
            uint8_t value = random(255);
            epd_draw_pixel(i, j, value, mNoiseFramebuffer);
         }
      }
      break;
   default:
      break;
   }
}
