#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "RandomSampleGenerator.h"

RandomSampleGenerator::RandomSampleGenerator()
   : width(0)
   , height(0)
   , linearPixelCoordinates()
   , currentLinearPixelCoordinate()
   , numSamplesGenerated(0)
{ }

RandomSampleGenerator::RandomSampleGenerator(const int width, const int height)
   : width(width)
   , height(height)
   , linearPixelCoordinates()
   , currentLinearPixelCoordinate()
   , numSamplesGenerated(0)
{
   linearPixelCoordinates.reserve(width * height);
}

RandomSampleGenerator::~RandomSampleGenerator()
{ }

void RandomSampleGenerator::generateCoordinates(int quadrantIndex)
{
   int halfWidth = width / 2;
   int halfHeight = height / 2;

   switch (quadrantIndex) {
   case 0: // Top left
      for (int i = 0; i < halfWidth; ++i) {
         for (int j = 0; j < halfHeight; ++j) {
            linearPixelCoordinates.push_back(i + j * width);
         }
      }
      std::cout << "0 - Generate coordinates of top left quadrant" << '\n';
      break;
   case 1: // Top right
      for (int i = halfWidth; i < width; ++i) {
         for (int j = 0; j < halfHeight; ++j) {
            linearPixelCoordinates.push_back(i + j * width);
         }
      }
      std::cout << "1 - Generate coordinates of top right quadrant" << '\n';
      break;
   case 2: // Bottom left
      for (int i = 0; i < halfWidth; ++i) {
         for (int j = halfHeight; j < height; ++j) {
            linearPixelCoordinates.push_back(i + j * width);
         }
      }
      std::cout << "2 - Generate coordinates of bottom left quadrant" << '\n';
      break;
   case 3: // Bottom right
      for (int i = halfWidth; i < width; ++i) {
         for (int j = halfHeight; j < height; ++j) {
            linearPixelCoordinates.push_back(i + j * width);
         }
      }
      std::cout << "3 - Generate coordinates of bottom right quadrant" << '\n';
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
   std::shuffle(linearPixelCoordinates.begin(), linearPixelCoordinates.end(), g);

   // Set the current coordinate to the beginning of the shuffled list
   currentLinearPixelCoordinate = linearPixelCoordinates.begin();
}

void RandomSampleGenerator::generateSample(Sample& sample)
{
   int currLinCoord = *currentLinearPixelCoordinate;

   int x = currLinCoord % width;
   int y = currLinCoord / width;

   // Update sample with the current coordinate
   sample.x = x;
   sample.y = y;

   // Move to the next coordinate in the shuffled list
   ++currentLinearPixelCoordinate;

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

