// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_MATRIXUTIL_H
#define SFM_MATRIXUTIL_H

#include "opencv2/core/core.hpp"
#include <iostream>
using namespace cv;
using namespace std;

class MatrixUtil {
public:
  static Mat_<double> getEulerAnglesByRotationMatrix(Mat_<double> &r);
};


#endif //SFM_MATRIXUTIL_H
