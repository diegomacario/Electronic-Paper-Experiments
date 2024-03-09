#ifndef RAY_GENERATOR_H
#define RAY_GENERATOR_H

#include "Sample.h"
#include "Ray.h"

/*
Description:

   The RayGenerator class is used to generate the rays that are shot through the center of each pixel on the image plane.
   Some designers like to refer to this class as the Camera class.

   Rays are generated in the same order samples are generated by the SampleGenerator class.
*/

class RayGenerator
{
public:

   RayGenerator();
   RayGenerator(const int width, const int height, const Point& eye, const Point& center, const Vector& up, float fovy);
   ~RayGenerator();

   void generateRay(const Sample& sample, Ray& ray);

private:

   int width, height;
   Point eye;
   Vector u, v, w;
   float alpha, beta;
};

#endif

