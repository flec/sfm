// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_MATRIXUTIL_H
#define SFM_MATRIXUTIL_H

#include "opencv2/core/core.hpp"
#include <iostream>
using namespace cv;
using namespace std;

/**
 * Utility functions for matrix operations
 */
class MatrixUtil {
public:
  /**
   * Returns a matrix of euler angles from a 3x3 rotation matrix
   * r        3x3 rotation matrix
   * returns  3x1 matrix with euler angles
   */
  static Mat_<double> getEulerAnglesByRotationMatrix(Mat_<double> &r);

  /**
   * Returns if the matrix is a valid intrinsic camera matrix
   * intrinsic  3x3 intrinsic matrix
   * returns    if valid
   */
  static bool isValidCameraIntrinsic(const Mat_<double> &intrinsic);
};


#endif //SFM_MATRIXUTIL_H
