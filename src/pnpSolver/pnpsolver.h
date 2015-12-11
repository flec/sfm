// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_PNPSOLVER_H
#define SFM_PNPSOLVER_H

#include "image/pair/imagepair.h"

/**
 * Interface for a perspective-n-point pose estimation
 * This is used to calculate the pose of a camera of a given image using the 3D object points and corresponding image points
 */
class PnPSolver {
public:
  /**
   * Estimates the camera pose of the second image in the image pair.
   * This is done by using the key point matches between the two images and corresponding 3D points of the first image.
   * The estimated pose is directly updated in the second image
   *
   * image_pair                   pair of images where the pose is estimated in the second image
   * intristic_camera_paramaters  intrinsic camera parameters
   */
  virtual void solve(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) = 0;
};

#endif //SFM_PNPSOLVER_H
