#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "RandomSampleGenerator.h"

RandomSampleGenerator::RandomSampleGenerator()
   : width(0)
   , height(0)
   , coordinates()
   , currentCoordinate()
   , numSamplesGenerated(0)
   , x(0)
   , y(0)
{ }

RandomSampleGenerator::RandomSampleGenerator(const int width, const int height)
   : width(width)
   , height(height)
   , coordinates()
   , currentCoordinate()
   , numSamplesGenerated(0)
   , x(0)
   , y(0)
{
   // Generate all possible (x, y) pairs
   // for (int y = 0; y < height; ++y)
   // {
   //     for (int x = 0; x < width; ++x)
   //     {
   //         coordinates.push_back({x, y});
   //     }
   // }

   // Shuffle the pairs
   // std::random_device rd;
   // std::mt19937 g(rd());
   // std::shuffle(coordinates.begin(), coordinates.end(), g);

   // Set the current coordinate to the beginning of the shuffled list
   // currentCoordinate = coordinates.begin();
}

RandomSampleGenerator::~RandomSampleGenerator()
{ }

void RandomSampleGenerator::generateSample(Sample& sample)
{
   // Update sample with the current coordinate
   // sample.x = currentCoordinate->first;
   // sample.y = currentCoordinate->second;

   // Move to the next coordinate in the shuffled list
   // ++currentCoordinate;

   sample.x = x;
   sample.y = y;

   ++x;
   if (x % width == 0) {
      x = 0;
      ++y;
   }

   // Increment the number of samples generated
   ++numSamplesGenerated;
}

bool RandomSampleGenerator::sampleIsAvailable()
{
   return (numSamplesGenerated != (width * height));
}

float RandomSampleGenerator::getProgress()
{
   return (static_cast<float>(numSamplesGenerated) / static_cast<float>(width * height));
}

