// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_CVPROJECTIONMATRIXFINDER_H
#define SFM_CVPROJECTIONMATRIXFINDER_H

#include "projectionmatrixfinder.h"

/**
 * Implementation of projection matrix finder that uses the OpenCV method.
 * The usage of distortion parameters for this calculation is currently not implemented
 */
class CvProjectionMatrixFinder : public ProjectionMatrixFinder {
public:
  /**
   * @see ProjectionMatrixFinder
   */
  void findProjectionMatrix(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters);
};

#endif //SFM_CVPROJECTIONMATRIXFINDER_H
