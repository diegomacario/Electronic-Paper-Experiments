#ifndef DATA_H
#define DATA_H

#include <string>

/*
Description:

   This file contains the following scene descriptions:

   - Sword
   - Rupee
   - Castle
   - Planet
   - Ice Cream
   - Pyramid
   - Spheres
   - Cake
   - Sphere
*/

std::vector<std::string> sceneDescriptions = {
// Sword
R"(
size 960 540
output sword.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

# Sideways
camera 0 6.5 -2.44 0 0 -2.44 -1 0 0 45

# Hilt
#camera  0 2 0.18 0 0 0.18 0 0 -1 45

# Bottom to top
#camera 0 3 8 0 0 0 0 1 0 45

# --- --- --- --- -- LIGHTS -- --- --- --- ---

attenuation 0 1 0
point 1.5 1 -4.333 1 1 1
point -1.5 1 -1.667 1 1 1
attenuation 0 1 10
point -1.5 1 2 0.25 0.25 0.25

# --- --- --- --- - GEOMETRY - --- --- --- ---

maxverts 50

# Blade
# --- --- --- --- --- --- --- --- ---

ambient  0.26 0.36  0.36
diffuse  0.3 0.5 0.5
specular 0.1 0.2 0.2
shininess 9999999999
maxdepth 5

# Outter face
vertex  0.355  0.175  0
vertex  0.355  0.175 -6
vertex  0      0.175 -7
vertex -0.355  0.175 -6
vertex -0.355  0.175  0
vertex  0      0.175 -2.842

# Inner face
vertex  0.667  0  0
vertex  0.667  0 -6.545
vertex  0      0 -8
vertex -0.667  0 -6.545
vertex -0.667  0  0

# Outter face (front)
tri 0 1 5
tri 1 2 5
tri 2 3 5
tri 3 4 5
tri 4 0 5
# Inner face (front)
tri 0 6 1
tri 6 7 1
tri 1 8 2
tri 1 7 8
tri 2 8 3
tri 3 8 9
tri 4 3 10
tri 10 3 9

pushTransform
rotate 0 0 1 180
# Outter face (back)
tri 0 1 5
tri 1 2 5
tri 2 3 5
tri 3 4 5
tri 4 0 5
# Inner face (back)
tri 0 6 1
tri 6 7 1
tri 1 8 2
tri 1 7 8
tri 2 8 3
tri 3 8 9
tri 4 3 10
tri 10 3 9
popTransform

# Cross-guard
# --- --- --- --- --- --- --- --- ---

# Yellow
ambient  1 0.5  0
diffuse  0 0.75 0
specular 0 0.25 0

# Top
vertex -1.334  0.375 0
vertex  1.334  0.375 0
vertex  1.334 -0.375 0
vertex -1.334 -0.375 0

# Bottom
vertex -0.667  0.375 0.36
vertex  0.667  0.375 0.36
vertex  0.667 -0.375 0.36
vertex -0.667 -0.375 0.36

# Top
tri 11 12 13
tri 11 13 14

# Bottom
tri 15 16 17
tri 15 17 18

# Front
tri 15 16 12
tri 15 12 11

# Back
tri 17 18 13
tri 13 18 14

# Right
tri 16 17 13
tri 16 13 12

# Left
tri 18 15 11
tri 18 11 14

# Hilt
# --- --- --- --- --- --- --- --- ---

ambient  0 0.3  0.3
diffuse  0.3 0.5 0.5
specular 0.1 0.2 0.2

# Top
vertex  0.32475  0.1875 0.36
vertex  0.32475 -0.1875 0.36
vertex  0        0      0.36
vertex  0       -0.375  0.36
vertex -0.32475 -0.1875 0.36
vertex -0.32475  0.1875 0.36
vertex  0        0.375  0.36

# Bottom
vertex  0.2598  0.15 2.76
vertex  0.2598 -0.15 2.76
vertex  0       0    2.76
vertex  0      -0.3  2.76
vertex -0.2598 -0.15 2.76
vertex -0.2598  0.15 2.76
vertex  0       0.3  2.76

pushTransform

rotate 0 0 1 30

# Top
tri 19 20 21
tri 20 22 21
tri 22 23 21
tri 23 24 21
tri 24 25 21
tri 25 19 21

## Bottom
tri 28 27 26
tri 28 29 27
tri 28 30 29
tri 28 31 30
tri 28 32 31
tri 28 26 32

# Hexagonal sides
ambient 0.24 0.071875 0.071875
tri 32 26 19
tri 32 19 25
ambient 0.138 0.0367 0.040625
tri 26 27 20
tri 26 20 19
ambient 0.24 0.071875 0.071875
tri 27 29 22
tri 27 22 20
ambient 0.138 0.0367 0.040625
tri 29 30 23
tri 29 23 22
ambient 0.24 0.071875 0.071875
tri 30 31 24
tri 30 24 23
ambient 0.138 0.0367 0.040625
tri 31 32 25
tri 31 25 24

popTransform

# Sphere
# --- --- --- --- --- --- --- --- ---

# Yellow
ambient 1 0.5 0
diffuse  0 0.75 0
specular 0 0.25 0

sphere 0 0 2.76 0.36

# Ruby
# --- --- --- --- --- --- --- --- ---

# Red
ambient 0.5 0.1 0.1
diffuse 0.5 0 0
specular 0.25 0 0

# Outter face
vertex  0     0.45  0
vertex  0     0.45  1.5
vertex  1.299 0.45  0.75
vertex  1.299 0.45 -0.75
vertex  0     0.45 -1.5
vertex -1.299 0.45 -0.75
vertex -1.299 0.45  0.75

# Inner face
vertex  0          0.375  2.25
vertex  1.94855716 0.375  1.125
vertex  1.94855716 0.375 -1.125
vertex  0          0.375 -2.25
vertex -1.94855716 0.375 -1.125
vertex -1.94855716 0.375  1.125

pushTransform

translate 0 0 0.18
scale 0.05 1 0.07

# Outter face
tri 33 34 35
tri 33 35 36
tri 33 36 37
tri 33 37 38
tri 33 38 39
tri 33 39 34

# Inner face
tri 40 35 34
tri 40 41 35
tri 41 36 35
tri 41 42 36
tri 42 37 36
tri 42 43 37
tri 43 38 37
tri 43 44 38
tri 44 39 38
tri 44 45 39
tri 45 34 39
tri 45 40 34

popTransform

pushTransform

# Emerald
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.3 0.3
diffuse 0 0.75 0
specular 0 0.25 0 

rotate 0 0 1 180
translate 0 0 0.18
scale 0.05 1 0.07

# Outter face
tri 33 34 35
tri 33 35 36
tri 33 36 37
tri 33 37 38
tri 33 38 39
tri 33 39 34

# Inner face
tri 40 35 34
tri 40 41 35
tri 41 36 35
tri 41 42 36
tri 42 37 36
tri 42 43 37
tri 43 38 37
tri 43 44 38
tri 44 39 38
tri 44 45 39
tri 45 34 39
tri 45 40 34

popTransform
)",

// Rupee
R"(
size 536 240 
output rupee.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

#camera 0 7 0 0 0 0 0 0 -1 45
camera 0 5 0 0 0 0 -1 0 0 45
#camera 0 3.5 0 0 0 0 -1 0 0 45

# --- --- --- --- -- LIGHTS -- --- --- --- ---

attenuation 0 1 0
point  1.5 1  1.5 1 1 1
point -1.5 1 -1.5 1 1 1

# --- --- --- --- - GEOMETRY - --- --- --- ---

maxverts 13

# Green
ambient  0 0.3  0.3
diffuse  0 0.75 0
specular 0 0.25 0
shininess 9999999999
maxdepth 5

# Outter face
vertex  0            0  0
vertex  0            0  1.5
vertex  0.789473684  0  0.947368421
vertex  0.789473684  0 -0.947368421
vertex  0            0 -1.5
vertex -0.789473684  0 -0.947368421
vertex -0.789473684  0  0.947368421

# Inner face
vertex  0            -0.5  2.307
vertex  1.359473684  -0.5  1.403507369
vertex  1.359473684  -0.5 -1.403507369
vertex  0            -0.5 -2.307
vertex -1.359473684  -0.5 -1.403507369
vertex -1.359473684  -0.5  1.403507369

pushTransform

translate 0 0.5 0

# Outter face (front)
# --- --- --- --- --- --- --- --- ---

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

# Inner face (front)
# --- --- --- --- --- --- --- --- ---

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1

popTransform

pushTransform

translate 0 -0.5 0
rotate 0 0 1 180

# Outter face (back)
# --- --- --- --- --- --- --- --- ---

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

# Inner face (back)
# --- --- --- --- --- --- --- --- ---

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1

popTransform
)",

// Castle
R"(
size 536 240
output castle.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

#camera 0.8 1.3 0.8 0 0 0 0 1 0 45
camera 0.7 0.9 0.7 0 0 0 0 1 0 45

# --- --- --- --- -- LIGHTS -- --- --- --- ---

attenuation 0 1 0
point 1 1.25 -1 1 1 1

# --- --- --- --- - GEOMETRY - --- --- --- ---

maxverts 7

diffuse 0 0.75 0
shininess 100
maxdepth 5

# Ground
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.3 0.3

vertex 1.5 0 1.5
vertex 1.5 0 -1.5
vertex -1.5 0 1.5
vertex -1.5 0 -1.5

pushTransform
scale 0.5 0.5 0.5
tri 0 1 2
tri 1 3 2
popTransform

# Castle body
# --- --- --- --- --- --- --- --- ---

# Cream
ambient 1 0.59 0.31

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Catle roof
# --- --- --- --- --- --- --- --- ---

vertex 0.15 0 0.15
vertex 0 0.212132034 0
vertex -0.15 0 0.15

# Blue
ambient 0 0.262 0.344

# Bottom
pushTransform
translate 0 0.3 0
rotate 1 0 0 180
scale 0.55 0.3 0.55
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

translate 0 0.3 0
scale 0.55 0.3 0.55
#scale 0.2 0.25 0.2

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

# Tower 1
# --- --- --- --- --- --- --- --- ---

# Cream
ambient 1 0.59 0.31

pushTransform

translate -0.12 0.3 0.12
scale 0.2 0.25 0.2

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tower 1 roof
# --- --- --- --- --- --- --- --- ---

# Red
ambient 0.803 0.172 0.141

pushTransform

translate -0.12 0.3 0.12
scale 0.2 0.25 0.2

# Bottom
pushTransform
translate 0 0.3 0
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

translate 0 0.3 0
scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tower 2
# --- --- --- --- --- --- --- --- ---

# Cream
ambient 1 0.59 0.31

pushTransform

translate -0.12 0.3 -0.12
scale 0.2 0.25 0.2

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tower 2 roof
# --- --- --- --- --- --- --- --- ---

# Red
ambient 0.803 0.172 0.141

pushTransform

translate -0.12 0.3 -0.12
scale 0.2 0.25 0.2

# Bottom
pushTransform
translate 0 0.3 0
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

translate 0 0.3 0
scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tower 3
# --- --- --- --- --- --- --- --- ---

# Cream
ambient 1 0.59 0.31

pushTransform

translate 0.12 0.3 0.12
scale 0.2 0.25 0.2

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tower 3 roof
# --- --- --- --- --- --- --- --- ---

# Red
ambient 0.803 0.172 0.141

pushTransform

translate 0.12 0.3 0.12
scale 0.2 0.25 0.2

# Bottom
pushTransform
translate 0 0.3 0
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

translate 0 0.3 0
scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tower 4
# --- --- --- --- --- --- --- --- ---

# Cream
ambient 1 0.59 0.31

pushTransform

translate 0.12 0.3 -0.12
scale 0.2 0.25 0.2

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tower 4 roof
# --- --- --- --- --- --- --- --- ---

# Red
ambient 0.803 0.172 0.141

pushTransform

translate 0.12 0.3 -0.12
scale 0.2 0.25 0.2

# Bottom
pushTransform
translate 0 0.3 0
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

translate 0 0.3 0
scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tree 1 trunk
# --- --- --- --- --- --- --- --- ---

# Brown
ambient 0.51 0.33 0.2

pushTransform

translate 0.525 0 0
scale 0.1 0.5 0.1

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tree 1 leaves
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.35 0.2

pushTransform 

translate 0.525 0.15 0
scale 0.25 0.65 0.25

# Bottom
pushTransform
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tree 2 trunk
# --- --- --- --- --- --- --- --- ---

# Brown
ambient 0.51 0.33 0.2

pushTransform

translate 0.4 0 -0.4
scale 0.1 0.5 0.1

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tree 2 leaves
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.35 0.2

pushTransform 

translate 0.4 0.15 -0.4
scale 0.25 0.65 0.25

# Bottom
pushTransform
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tree 3 trunk
# --- --- --- --- --- --- --- --- ---

# Brown
ambient 0.51 0.33 0.2

pushTransform

translate 0 0 -0.5225
scale 0.1 0.5 0.1

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tree 3 leaves
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.35 0.2

pushTransform 

translate 0 0.15 -0.5225
scale 0.25 0.65 0.25

# Bottom
pushTransform
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tree 4 trunk
# --- --- --- --- --- --- --- --- ---

# Brown
ambient 0.51 0.33 0.2

pushTransform

translate -0.45 0 -0.3
scale 0.1 0.5 0.1

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tree 4 leaves
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.35 0.2

pushTransform 

translate -0.45 0.15 -0.3
scale 0.25 0.65 0.25

# Bottom
pushTransform
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tree 5 trunk
# --- --- --- --- --- --- --- --- ---

# Brown
ambient 0.51 0.33 0.2

pushTransform

translate -0.45 0 0.25
scale 0.1 0.5 0.1

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tree 5 leaves
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.35 0.2

pushTransform 

translate -0.45 0.15 0.25
scale 0.25 0.65 0.25

# Bottom
pushTransform
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tree 6 trunk
# --- --- --- --- --- --- --- --- ---

# Brown
ambient 0.51 0.33 0.2

pushTransform

translate -0.1 0 0.475
scale 0.1 0.5 0.1

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tree 6 leaves
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.35 0.2

pushTransform 

translate -0.1 0.15 0.475
scale 0.25 0.65 0.25

# Bottom
pushTransform
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform

# Tree 7 trunk
# --- --- --- --- --- --- --- --- ---

# Brown
ambient 0.51 0.33 0.2

pushTransform

translate 0.33 0 0.355
scale 0.1 0.5 0.1

# Back
pushTransform
translate 0 0.15 -0.15 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Left
pushTransform
translate -0.15 0.15 0
rotate 0 1 0 90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Right
pushTransform
translate 0.15 0.15 0
rotate 0 1 0 -90 
rotate 1 0 0 -90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Front
pushTransform
translate 0 0.15 0.15 
rotate 1 0 0 90
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

# Top
pushTransform
translate 0 0.3 0 
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

popTransform

# Tree 7 leaves
# --- --- --- --- --- --- --- --- ---

# Green
ambient 0 0.35 0.2

pushTransform

translate 0.33 0.15 0.355
scale 0.25 0.65 0.25

# Bottom
pushTransform
rotate 1 0 0 180
scale 1.25 1 1.25
scale 0.1 0.1 0.1
tri 0 1 2
tri 1 3 2
popTransform

pushTransform

scale 1.25 1 1.25

# Front
pushTransform 
tri 4 5 6
popTransform

# Back
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform

popTransform

popTransform
)",

// Planet
R"(
size 536 240
output tralfamadore.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

camera 0 0 0.7 0 0 0 0 1 0 40

# --- --- --- --- -- LIGHTS -- --- --- --- ---

point -0.5 1 1 0.9 0.9 0.9
point -0.5 -1 1 0.9 0.9 0.9

# --- --- --- --- - GEOMETRY - --- --- --- ---

# Planet
# --- --- --- --- --- --- --- --- ---

ambient 0.05 0.05 0.05
diffuse 0.247059 0.0431373 0.105882

sphere 0 0 0 0.175

# Rings
# --- --- --- --- --- --- --- --- ---

pushTransform

# Tilt the rings
rotate 0 0 1 -15
rotate 1 0 0 15

# First ring (inner)
diffuse 0.478431 0.0862745 0.192157
pushTransform
   scale 0.8 0.016875 0.8
   sphere 0 0 0 0.3
popTransform

# Second ring
diffuse 0.811765 0.258824 0.235294
pushTransform
   scale 0.86 0.0140625 0.86
   sphere 0 0 0 0.3
popTransform

# Third ring
diffuse 0.988235 0.490196 0.286275
pushTransform
   scale 0.93 0.009375 0.93
   sphere 0 0 0 0.3
popTransform

# Fourth ring (outter)
diffuse 1 0.831373 0.384314
pushTransform
   scale 1 0.0046875 1
   sphere 0 0 0 0.3
popTransform

popTransform

# Stars
# --- --- --- --- --- --- --- --- ---

ambient 1 1 1
diffuse 0 0 0

# CCWISE quadrants
sphere 0.3 0.2 0 0.004
sphere -0.3 0.2 0 0.004
sphere -0.3 -0.2 0 0.004
sphere 0.3 -0.2 0 0.004

# CCWISE quadrants shifted left
sphere 0.2 0.3 0 0.004
sphere -0.2 0.3 0 0.004
sphere -0.2 -0.3 0 0.004
sphere 0.2 -0.3 0 0.004

# CCWISE quadrants shifted left (Low)
sphere 0.15 0.19 0 0.004
sphere -0.15 0.19 0 0.004
sphere -0.15 -0.19 0 0.004
sphere 0.15 -0.19 0 0.004

# CCWISE axes
sphere 0.375 0 0 0.004
sphere 0 0.275 0 0.004
sphere -0.375 0 0 0.004
sphere 0 -0.275 0 0.004

# CCWISE corners
sphere 0.4 0.3 0 0.004
sphere -0.4 0.3 0 0.004
sphere -0.4 -0.3 0 0.004
sphere 0.4 -0.3 0 0.004

# CCWISE corners (low)
sphere 0.415 0.15 0 0.004
sphere -0.415 0.15 0 0.004
sphere -0.415 -0.15 0 0.004
sphere 0.415 -0.15 0 0.004

# CCWISE axes shifted left
sphere 0.25 0.075 0 0.004
sphere -0.25 -0.075 0 0.004
)",

// Ice Cream
R"(
size 536 240
output ice_cream_sunrise_hexagon.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

#camera 1.5 3.5 1.5 -0.5 0 -0.5 0 1 0 45
camera 1.7 3.7 1.7 -0.5 0 -0.5 0 1 0 45

# --- --- --- --- -- LIGHTS -- --- --- --- ---

attenuation 0 1 0
point 0.4 1 -1.6 1 1 1

# --- --- --- --- - GEOMETRY - --- --- --- ---

maxverts 7

# Scoops of ice cream
# --- --- --- --- --- --- --- --- ---

# Non-reflective material
diffuse 0 0.75 0

# Base (blue)
ambient 0.122 0.541 0.439
sphere -0.6 0.375 -0.6 0.375

# Middle (green)
ambient 0.745 0.859 0.224
sphere -0.6 1.05 -0.6 0.3

# Top (yellow)
ambient 0.9 0.9 0.102
sphere -0.6 1.575 -0.6 0.225

# Desert floor
# --- --- --- --- --- --- --- --- ---

# Reflective material (orange)
ambient 0.992 0.455 0
specular 0 0.25 0
shininess 100

vertex 1.299 0 0.75
vertex 1.299 0 -0.75
vertex 0 0 0
vertex 0 0 -1.5
vertex -1.299 0 -0.75
vertex -1.299 0 0.75
vertex 0 0 1.5

translate -0.6 0 -0.6
rotate 0 1 0 -15
scale 1.2 0 1.2

tri 0 1 2
tri 1 3 2
tri 3 4 2
tri 4 5 2
tri 5 6 2
tri 6 0 2
)",

// Pyramid
R"(
size 536 240
output pyramid_red.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

camera 1 0.5 1 0 0 0 0 1 0 45

# --- --- --- --- -- LIGHTS -- --- --- --- ---

attenuation 0 1 0
point 0.76 1 -1.24 1 1 1

# --- --- --- --- - GEOMETRY - --- --- --- ---

maxverts 7

# --- FLOOR ---

# Red
ambient 0.5 0.1 0.1
diffuse 0.5 0 0
specular 0.25 0 0
shininess 100
maxdepth 5

vertex 1.5 0 1.5
vertex 1.5 0 -1.5
vertex -1.5 0 1.5
vertex -1.5 0 -1.5

translate -0.24 0 -0.24

pushTransform
scale 0.5 0.5 0.5
tri 0 1 2
tri 1 3 2
popTransform

# Pyramid
# --- --- --- --- --- --- --- --- ---

# Yellow
diffuse 0 0.75 0
specular 0 0.25 0
ambient 1 0.5 0

vertex 0.15 0 0.15
vertex 0 0.212132034 0
vertex -0.15 0 0.15

scale 2 2 2

# Front of pyramid
pushTransform 
tri 4 5 6
popTransform

# Back of pyramid
pushTransform
rotate 0 1 0 180 
tri 4 5 6
popTransform

# Left of pyramid
pushTransform
rotate 0 1 0 -90 
tri 4 5 6
popTransform

# Right of pyramid
pushTransform
rotate 0 1 0 90 
tri 4 5 6
popTransform
)",

// Spheres
R"(
size 536 240
output four_spheres.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

camera 0 0 -2 0 0.75 -2 0 0 1 45

# --- --- --- --- -- LIGHTS -- --- --- --- ---

attenuation 0 1 0
point 0 0 0 1 1 1

# --- --- --- --- - GEOMETRY - --- --- --- ---

diffuse 0 0.5 0 
specular 0.75 0.75 0.75 
shininess 100000
maxdepth 5

# Green
ambient 0.2 0.4 0.1
sphere -0.75 0 -2 0.5

# Yellow
ambient 0.5 0.5 0
sphere 0.75 0 -2 0.5

# Red
ambient 0.75 0 0
sphere 0 -0.75 -2 0.5

# Blue
ambient 0 0.262 0.344
sphere 0 0.75 -2 0.5
)",

// Cake
R"(
size 536 240
output cake.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

# Full cake
camera 0 1.25 3.5 0 -0.7 0 0 0 -1 45

# Close-up of candle
#camera 0 0.625 1.25 0 0.428571 0 0 0 -1 45

# --- --- --- --- -- LIGHTS -- --- --- --- ---

attenuation 0 1 0
point 0 1 0 0.75 0.4 0

# --- --- --- --- - GEOMETRY - --- --- --- ---

maxverts 13

# No reflections
specular 0 0 0
maxdepth 0

# Top hexagon
vertex  0      0.142857   0
vertex  0      0.142857   1.5
vertex  1.299  0.142857   0.75
vertex  1.299  0.142857  -0.75
vertex  0      0.142857  -1.5
vertex -1.299  0.142857  -0.75
vertex -1.299  0.142857   0.75

# Bottom hexagon
vertex  0      0  1.5
vertex  1.299  0  0.75
vertex  1.299  0 -0.75
vertex  0      0 -1.5
vertex -1.299  0 -0.75
vertex -1.299  0  0.75

# Layers (listed from bottom to top)
# --- --- --- --- --- --- --- --- ---

# Frosting 1
# --- --- ---

ambient 0.35 0.35 0.35
diffuse 1 1 1

pushTransform
translate 0 -1 0

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1
popTransform

# Chocolate 1
# --- --- ---

ambient 0.1 0.05 0
diffuse 1 1 1

pushTransform
translate 0 -0.857143 0
scale 1 2 1

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1
popTransform

# Frosting 2
# --- --- ---

ambient 0.35 0.35 0.35
diffuse 1 1 1

pushTransform
translate 0 -0.571429 0

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1
popTransform

# Chocolate 2
# --- --- ---

ambient 0.1 0.05 0
diffuse 1 1 1

pushTransform
translate 0 -0.428572 0
scale 1 2 1

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1
popTransform

# Frosting 3
# --- --- ---

ambient 0.5 0.5 0.5
diffuse 1 1 1

pushTransform
translate 0 -0.142857 0

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

ambient 0.35 0.35 0.35

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1
popTransform

# Strawberries
# --- --- --- --- --- --- --- --- ---

ambient 0.5 0 0
diffuse 1 1 1

pushTransform
sphere 0.77425 0 0 0.1
popTransform

pushTransform
rotate 0 1 0 60
sphere 0.77425 0 0 0.1
popTransform

pushTransform
rotate 0 1 0 120
sphere 0.77425 0 0 0.1
popTransform

pushTransform
rotate 0 1 0 180
sphere 0.77425 0 0 0.1
popTransform

pushTransform
rotate 0 1 0 240
sphere 0.77425 0 0 0.1
popTransform

pushTransform
rotate 0 1 0 300
sphere 0.77425 0 0 0.1
popTransform

# Candle
# --- --- --- --- --- --- --- --- ---

ambient  0 0.4  0.4
diffuse  0.3 0.5 0.5

pushTransform
scale 0.05 3 0.05

tri 0 1 2
tri 0 2 3
tri 0 3 4
tri 0 4 5
tri 0 5 6
tri 0 6 1

tri 7 2 1
tri 7 8 2
tri 8 3 2
tri 8 9 3
tri 9 4 3
tri 9 10 4
tri 10 5 4
tri 10 11 5
tri 11 6 5
tri 11 12 6
tri 12 1 6
tri 12 7 1
popTransform

# Flame
# --- --- --- --- --- --- --- --- ---

ambient 0.9 0.375 0
diffuse 0.9 0.375 0
specular 1 1 1

pushTransform
translate 0 -0.0125 0
scale 0.61 1 0.61

sphere 0 0.428571 0 0.1
popTransform
)",

// Sphere
R"(
size 960 540
output sphere.png

# --- --- --- --- -- CAMERA -- --- --- --- ---

camera 0 0 0.7 0 0 0 0 1 0 40

# --- --- --- --- -- LIGHTS -- --- --- --- ---

point -0.5 1 1 0.9 0.9 0.9
point -0.5 -1 1 0.9 0.9 0.9

# --- --- --- --- - GEOMETRY - --- --- --- ---

# Sphere
# --- --- --- --- --- --- --- --- ---

ambient 0.05 0.05 0.05
diffuse 0.247059 0.0431373 0.105882

sphere 0 0 0 0.175

# Rings
# --- --- --- --- --- --- --- --- ---

pushTransform

# Tilt the rings
rotate 0 0 1 -15
rotate 1 0 0 15

# First ring (inner)
diffuse 0.478431 0.0862745 0.192157
pushTransform
   scale 0.8 0.016875 0.8
   sphere 0 0 0 0.3
popTransform

# Second ring
diffuse 0.811765 0.258824 0.235294
pushTransform
   scale 0.86 0.0140625 0.86
   sphere 0 0 0 0.3
popTransform

# Third ring
diffuse 0.988235 0.490196 0.286275
pushTransform
   scale 0.93 0.009375 0.93
   sphere 0 0 0 0.3
popTransform

# Fourth ring (outter)
diffuse 1 0.831373 0.384314
pushTransform
   scale 1 0.0046875 1
   sphere 0 0 0 0.3
popTransform

popTransform
)"};

// const std::string ...SceneDescription = R"(
// )";

#endif

