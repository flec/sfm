// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iostream>
#include <iomanip>
#include "basicprojectionmatrixfinder.h"

using namespace std;

void BasicProjectionMatrixFinder::findProjectionMatrix(shared_ptr<ImagePair> &image_pair,
                                                       Mat &intrinsic_camera_parameters) {
  // calculating the projection matrix K * [R|t]
  *image_pair->image1->camera()->projection() = intrinsic_camera_parameters * *image_pair->image1->camera()->extrinsic();
  *image_pair->image2->camera()->projection() = intrinsic_camera_parameters * *image_pair->image2->camera()->extrinsic();
}