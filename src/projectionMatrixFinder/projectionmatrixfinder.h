// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_PROJECTIONMATRIXFINDER_H
#define SFM_PROJECTIONMATRIXFINDER_H


#include <memory>
#include "image/pair/imagepair.h"
/**
 * Interface for calculating the projection matrix for an image based on camera pose and intrinsic camera parameters
 */
class ProjectionMatrixFinder {
public:
  /**
   * Calculates the projection matrix for both images in the pair.
   * The calculation uses the camera pose and intrinsic parameters
   *
   * image_pair                   image pair with images containing camera parameters
   * intrinsic_camera_parameters  intrinsic camera parameters
   */
  virtual void findProjectionMatrix(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters) = 0;
};

#endif //SFM_PROJECTIONMATRIXFINDER_H
