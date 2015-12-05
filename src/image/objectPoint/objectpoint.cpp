//
// Created by marco on 18.11.15.
//

#include <opencv2/core/mat.hpp>
#include <iostream>
#include "objectpoint.h"
#include "image/image.h"

using namespace std;
using namespace cv;

Mat_<float> ObjectPoint::rotate_x_axis_180 = (Mat_<float>(3, 3) << 1, 0, 0, 0, -1, 0, 0, 0, -1);

void ObjectPoint::updateCoordinates(float x, float y, float z) {
  coordinates_.x = x;
  coordinates_.y = y;
  coordinates_.z = z;
}

void ObjectPoint::addReference(int keypointIndex, shared_ptr<Image> image) {
  references_.push_back(KeyPointImagePair(keypointIndex, image));
}

ObjectPoint::ObjectPoint(float x, float y, float z) :
    coordinates_(x, y, z) {
  Mat gl_coordinates_mat = rotate_x_axis_180 * Mat(coordinates_, false);
  gl_coordinates_mat.copyTo(Mat(gl_coordinates_, false));
}

void ObjectPoint::removeReferencesToImage(shared_ptr<Image> image) {
  int i;
  for (auto reference : references_) {
    if (reference.image == image) {
      references_.erase(references_.begin() + i);
    }
    else
      ++i;
  }
}

void ObjectPoint::recalculateColor() {
  Point3_<uint> sum_colors(0, 0, 0);

  for (auto reference : references_) {
    Point3_<uchar> *color = reference.image->mat_color()->ptr<Point3_<uchar> >(reference.key_point->pt.y, reference.key_point->pt.x);
    sum_colors.x += (int) color->x;
    sum_colors.y += (int) color->y;
    sum_colors.z += (int) color->z;
  }

  color_.x = ((float) sum_colors.z / references_.size()) / 255;
  color_.y = ((float) sum_colors.y / references_.size()) / 255;
  color_.z = ((float) sum_colors.x / references_.size()) / 255;
}
