// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_CAMERAMATRIXFINDER_H
#define SFM_CAMERAMATRIXFINDER_H

#include <opencv2/core/cvdef.h>
#include "opencv2/core/core.hpp"
#include <memory>
#include "image/pair/imagepair.h"

using namespace cv;
using namespace std;

/**
 * Interface for finding a camera matrices between two images.
 */
class CameraMatrixFinder {
public:
  /**
   * Find the camera matrices between two images. Therefore the following matrices will be updated in the ImagePair:
   *   - essential
   *   - rotation
   *   - translation
   * As an input the matches between the features in the ImagePair must have been calculated.
   *
   *  image_pair                    The ImagePair
   *  intristic_camera_paramaters   Intrinsic parameters of the camera - must be the same for both images:
   *                                fx 0  cx
   *                                0  fy cy
   *                                0  0  1
   */
  virtual void findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) = 0;

protected:
  /**
   * After the calculation of the essential matrix between two images, one has several outliners of feature matches,
   * that don't agree to that matrix. They need to be removed, to be consistent.
   *
   * image_pair   The ImagePair
   * inliners     1D cv::Mat<char> containing 1 if the match at index i is an inliner, otherwise it shall contain 0. If
   *              index i has a value of 0, the match at index i will be removed from the ImagePait.
   */
  void removeOutlinerMatches(shared_ptr<ImagePair> &image_pair, Mat &inliners);
};

#endif // SFM_CAMERAMATRIXFINDER_H