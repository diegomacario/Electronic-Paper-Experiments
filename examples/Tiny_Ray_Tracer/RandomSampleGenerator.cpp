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
{ }

RandomSampleGenerator::RandomSampleGenerator(const int width, const int height)
   : width(width)
   , height(height)
   , coordinates()
   , currentCoordinate()
   , numSamplesGenerated(0)
{ }

RandomSampleGenerator::~RandomSampleGenerator()
{ }

void RandomSampleGenerator::generateCoordinates(int quadrantIndex)
{
   int halfWidth = width / 2;
   int halfHeight = height / 2;

   switch (quadrantIndex) {
   case 0: // Top left
      std::cout << "0 - Generate coordinates of top left quadrant" << '\n';
      for (int i = 0; i < halfWidth; ++i) {
         for (int j = 0; j < halfHeight; ++j) {
            coordinates.push_back({i, j});
         }
      }
      break;
   case 1: // Top right
      std::cout << "1 - Generate coordinates of top right quadrant" << '\n';
      for (int i = halfWidth; i < width; ++i) {
         for (int j = 0; j < halfHeight; ++j) {
            coordinates.push_back({i, j});
         }
      }
      break;
   case 2: // Bottom left
      std::cout << "2 - Generate coordinates of bottom left quadrant" << '\n';
      for (int i = 0; i < halfWidth; ++i) {
         for (int j = halfHeight; j < height; ++j) {
            coordinates.push_back({i, j});
         }
      }
      break;
   case 3: // Bottom right
      std::cout << "3 - Generate coordinates of bottom right quadrant" << '\n';
      for (int i = halfWidth; i < width; ++i) {
         for (int j = halfHeight; j < height; ++j) {
            coordinates.push_back({i, j});
         }
      }
      break;
   default:
      break;
   }
}

void RandomSampleGenerator::shuffleCoordinates() {
   std::cout << "Shuffle coordinates" << '\n';

   // Shuffle the pairs
   std::random_device rd;
   std::mt19937 g(rd());
   std::shuffle(coordinates.begin(), coordinates.end(), g);

   // Set the current coordinate to the beginning of the shuffled list
   currentCoordinate = coordinates.begin();
}

void RandomSampleGenerator::generateSample(Sample& sample)
{
   // Update sample with the current coordinate
   sample.x = currentCoordinate->first;
   sample.y = currentCoordinate->second;

   // Move to the next coordinate in the shuffled list
   ++currentCoordinate;

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

