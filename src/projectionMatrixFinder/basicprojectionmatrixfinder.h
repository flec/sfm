// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_BASICPROJECTIONMATRIXFINDER_H
#define SFM_BASICPROJECTIONMATRIXFINDER_H

#include "projectionmatrixfinder.h"

/**
 * Implementation of a projection matrix finder.
 * This finder uses only rotation and translation (pose) of the camera.
 * Distortion parameters are not used in this implementation.
 */
class BasicProjectionMatrixFinder : public ProjectionMatrixFinder {
public:
  /**
   * @see ProjectionMatrixFinder
   */
  Mat findProjectionMatrix(Mat &intrinsic_camera_parameters,
                                                        Mat &extrinsic_camera_parameters);
};

#endif //SFM_BASICPROJECTIONMATRIXFINDER_H
