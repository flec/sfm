// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_RANSACCAMERAMATRIXFINDER_H
#define SFM_RANSACCAMERAMATRIXFINDER_H

#include "cameramatrixfinder.h"

class RANSACCameraMatrixFinder : public CameraMatrixFinder{
public:
  void findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters);
};


#endif //SFM_RANSACCAMERAMATRIXFINDER_H
