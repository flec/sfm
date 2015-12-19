// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iostream>
#include <iomanip>
#include "basicprojectionmatrixfinder.h"

using namespace std;

Mat BasicProjectionMatrixFinder::findProjectionMatrix(Mat &intrinsic_camera_parameters,
                                                      Mat &extrinsic_camera_parameters) {
  // calculating the projection matrix K * [R|t]
  return intrinsic_camera_parameters * extrinsic_camera_parameters;
}