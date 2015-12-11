// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_PROJECTIONMATRIXFINDER_H
#define SFM_PROJECTIONMATRIXFINDER_H


#include <memory>
#include "image/pair/imagepair.h"

class ProjectionMatrixFinder {
public:
  virtual void findProjectionMatrix(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) = 0;
};

#endif //SFM_PROJECTIONMATRIXFINDER_H
