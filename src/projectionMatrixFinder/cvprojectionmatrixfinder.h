// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_CVPROJECTIONMATRIXFINDER_H
#define SFM_CVPROJECTIONMATRIXFINDER_H

#include "projectionmatrixfinder.h"

class CvProjectionMatrixFinder : public ProjectionMatrixFinder {
public:
  void findProjectionMatrix(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters);
};

#endif //SFM_CVPROJECTIONMATRIXFINDER_H
