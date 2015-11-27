//
// Created by marco on 18.11.15.
//

#include <opencv2/core/mat.hpp>
#include <iostream>
#include "objectpoint.h"

using namespace std;
using namespace cv;

Mat_<float> ObjectPoint::rotate_x_axis_180 = (Mat_<float>(3, 3) << 1, 0, 0, 0, -1, 0, 0, 0, -1);

void ObjectPoint::addReference(int keypointIndex, shared_ptr<Image> image) {
  this->refKeypoints.push_back(keypointIndex);
  this->refImages.push_back(image);
}

ObjectPoint::ObjectPoint(float x, float y, float z, float r, float g, float b) :
    coordinates_(x, y, z), color_(r, g, b) {
  Mat gl_coordinates_mat = rotate_x_axis_180 * Mat(coordinates_, false);
  gl_coordinates_mat.copyTo(Mat(gl_coordinates_, false));
}
