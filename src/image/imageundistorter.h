// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_IMAGEUNDISTORTER_H
#define SFM_IMAGEUNDISTORTER_H

#include <opencv2/core/mat.hpp>
#include "image.h"

using namespace cv;

/**
 * Class for undistorting images
 */
class ImageUndistorter {
public:
  /**
   * Undistorts a vector of images
   */
  static void undistort(vector<shared_ptr<Image>> images, Mat &intrinsic, Mat &distortion_coefficients);
};
#endif //SFM_IMAGEUNDISTORTER_H
