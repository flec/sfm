// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iostream>
#include <iomanip>
#include "basicprojectionmatrixfinder.h"

using namespace std;

void BasicProjectionMatrixFinder::findProjectionMatrix(shared_ptr<ImagePair> &image_pair,
                                                       Mat &intristic_camera_paramaters) {
  image_pair->projection_img1 = intristic_camera_paramaters * *image_pair->image1->camera()->extrinsic();
  image_pair->projection_img2 = intristic_camera_paramaters * *image_pair->image2->camera()->extrinsic();
}