//
// Created by marco on 18.11.15.
//

#include <iostream>
#include <iomanip>
#include "basicprojectionmatrixfinder.h"

using namespace std;

void BasicProjectionMatrixFinder::findProjectionMatrix(shared_ptr<ImagePair> &image_pair,
                                                       Mat &intristic_camera_paramaters) {
  image_pair->projection_img1 = intristic_camera_paramaters * *image_pair->image1->camera()->rotation_translation();
  image_pair->projection_img2 = intristic_camera_paramaters * *image_pair->image2->camera()->rotation_translation();
}