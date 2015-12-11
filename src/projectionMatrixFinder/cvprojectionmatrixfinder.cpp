// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "cvprojectionmatrixfinder.h"
#include <opencv2/calib3d.hpp>
#include <iostream>

void CvProjectionMatrixFinder::findProjectionMatrix(shared_ptr<ImagePair> &image_pair,
                                                    Mat &intristic_camera_paramaters) {

  Mat D1 = Mat::zeros(1, 5, CV_64F);
  Mat D2 = Mat::zeros(1, 5, CV_64F);
  Mat Q;
  Size imgSize = image_pair->image1->mat_grey()->size();
  stereoRectify(intristic_camera_paramaters, D1, intristic_camera_paramaters, D2,
                imgSize, image_pair->rotation, image_pair->translation,
                image_pair->rotation_rect_img1, image_pair->rotation_rect_img2,
                image_pair->projection_img1, image_pair->projection_img2, Q);
}