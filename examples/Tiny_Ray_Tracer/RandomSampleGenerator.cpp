#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "RandomSampleGenerator.h"

RandomSampleGenerator::RandomSampleGenerator()
   : width(0)
   , height(0)
   , x(0)
   , y(0)
   , bit(0)
   , random(1)
   , filledPixels()
   , numSamplesGenerated(0)
   , numRepeatedPixels(0)
{ }

RandomSampleGenerator::RandomSampleGenerator(const int width, const int height)
   : width(width)
   , height(height)
   , x(0)
   , y(0)
   , bit(0)
   , random(1)
   , filledPixels()
   , numSamplesGenerated(0)
   , numRepeatedPixels(0)
{
   filledPixels.resize(width * height, false);
}

RandomSampleGenerator::~RandomSampleGenerator()
{ }

void RandomSampleGenerator::generateSample(Sample& sample)
{
   int linearPixelPosition = x + (y * width);

   if (filledPixels[linearPixelPosition]) {
      while (filledPixels[linearPixelPosition]) {
         bit = ((random >> 0) ^ (random >> 2) ^ (random >> 3) ^ (random >> 5)) & 1;
         random =  (random >> 1) | (bit << 15);
         x = random % width;
         y = random / width;
         linearPixelPosition = x + (y * width);
         ++numRepeatedPixels;
      }

      sample.x = x;
      sample.y = y;
      filledPixels[linearPixelPosition] = true;
   } else {
      sample.x = x;
      sample.y = y;
      filledPixels[linearPixelPosition] = true;
   }

   bit = ((random >> 0) ^ (random >> 2) ^ (random >> 3) ^ (random >> 5)) & 1;
   random =  (random >> 1) | (bit << 15);
   x = random % width;
   y = random / width;

   ++numSamplesGenerated;
}

bool RandomSampleGenerator::sampleIsAvailable()
{
   // std::cout << "Num repeated: " << numRepeatedPixels << '\n';
   // std::cout << "Num samples: " << numSamplesGenerated << '\n';
   // bool sampleIsAvail = (numSamplesGenerated != (width * height));
   // if (!sampleIsAvail) {
   //    if (std::all_of(filledPixels.begin(), filledPixels.end(), [](bool v) { return v; })) {
   //       printf("All pixels filled!");
   //    } else {
   //       printf("Not all pixels filled!");
   //    }
   // }
   return (numSamplesGenerated != (width * height));
}

float RandomSampleGenerator::getProgress()
{
   return (static_cast<float>(numSamplesGenerated) / static_cast<float>(width * height));
}

