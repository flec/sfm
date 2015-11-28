/*
* Interface for triangulator
*/

#pragma once

#include <memory>
#include "image/pair/imagepair.h"

// Triangulates 2D points to obtain 3D points
class Triangulator
{
public:
  // computes homogenous 3D points for an image pair
  virtual void findPoints3D(shared_ptr<ImagePair> &image_pair, vector <Point3f> &points3D) = 0;

};
