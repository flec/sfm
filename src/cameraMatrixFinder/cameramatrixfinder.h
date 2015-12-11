// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_CAMERAMATRIXFINDER_H
#define SFM_CAMERAMATRIXFINDER_H

#pragma once

#include <memory>
#include "image/pair/imagepair.h"

using namespace cv;
using namespace std;

class CameraMatrixFinder
{
public:
  virtual void findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat& intristic_camera_paramaters) = 0;
protected:
  void removeOutlinerMatches(shared_ptr<ImagePair> &image_pair, Mat &inliners);
};

#endif // SFM_CAMERAMATRIXFINDER_H