// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <memory>
#include "image/pair/imagepair.h"

// Triangulates 2D points to obtain 3D points
class Triangulator
{
public:
  // computes homogenous 3D points for an image pair
  virtual void findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters, map<int, Point3f> &map_points3D) = 0;

};
