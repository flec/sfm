// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "matrixutil.h"
#include <math.h>

Mat_<double> MatrixUtil::getEulerAnglesByRotationMatrix(Mat_<double> &r) {
  double Ry1 = -1 * asin(r.at<double>(2, 0));
  double Ry2 = M_PI - Ry1;
  double Rx1 = atan2(r.at<double>(2, 1) / cos(Ry1), r.at<double>(2, 2) / cos(Ry1));
  double Rx2 = atan2(r.at<double>(2, 1) / cos(Ry2), r.at<double>(2, 2) / cos(Ry2));
  double Rz1 = atan2(r.at<double>(1, 0) / cos(Ry1), r.at<double>(0, 0) / cos(Ry1));
  double Rz2 = atan2(r.at<double>(1, 0) / cos(Ry2), r.at<double>(0, 0) / cos(Ry2));

  Mat_<double> angles1 = (Mat_<double>(3, 1) << Rx1, Ry1, Rz1);
  Mat_<double> angles2 = (Mat_<double>(3, 1) << Rx2, Ry2, Rz2);
  return angles1;
}

bool MatrixUtil::isValidCameraIntrinsic(const Mat_<double> &intrinsic) {
  return intrinsic.cols == 3 && intrinsic.rows == 3 &&
      intrinsic.at<double>(0,0) != 0 && intrinsic.at<double>(1,1) != 0 &&
      intrinsic.at<double>(0,2) != 0 && intrinsic.at<double>(1,2) != 0 && intrinsic.at<double>(2,2) == 1;
}
