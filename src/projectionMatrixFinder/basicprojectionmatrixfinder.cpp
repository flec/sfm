//
// Created by marco on 18.11.15.
//

#include <iostream>
#include <iomanip>
#include "basicprojectionmatrixfinder.h"

using namespace std;

void BasicProjectionMatrixFinder::findProjectionMatrix(shared_ptr<ImagePair> &image_pair,
                                                       Mat &intristic_camera_paramaters) {
  Mat_<double> r = image_pair->rotation;
  Mat_<double> t = image_pair->translation;
  Mat_<double> Rt1 = Mat::eye(3, 4, CV_64FC1);
  Mat_<double> Rt2;
  Rt2 = (Mat_<double>(3, 4) <<
         r(0, 0), r(0, 1), r(0, 2), t(0),
      r(1, 0), r(1, 1), r(1, 2), t(1),
      r(2, 0), r(2, 1), r(2, 2), t(2));

  image_pair->projection_img1 = intristic_camera_paramaters * Rt1;
  image_pair->projection_img2 = intristic_camera_paramaters * Rt2;

}