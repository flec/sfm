// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "cvprojectionmatrixfinder.h"
#include <opencv2/calib3d.hpp>
#include <iostream>

void CvProjectionMatrixFinder::findProjectionMatrix(shared_ptr<ImagePair> &image_pair,
                                                    Mat &intrinsic_camera_parameters) {

  Mat distortion_coefficients1 = Mat::zeros(1, 5, CV_64F);
  Mat distortion_coefficients2 = Mat::zeros(1, 5, CV_64F);
  Mat q;
  Mat rotation_rectified1;
  Mat rotation_rectified2;
  Size image_size = image_pair->image1->mat_grey()->size();

  // calculate projection matrix using openCV function
  stereoRectify(intrinsic_camera_parameters, distortion_coefficients1, intrinsic_camera_parameters,
                distortion_coefficients2,
                image_size, image_pair->rotation, image_pair->translation,
                rotation_rectified1, rotation_rectified2,
                *image_pair->image1->camera()->projection(), *image_pair->image2->camera()->projection(), q);
}