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

void ObjectPoint::addReference(int keypointIndex, shared_ptr<Image> image) {
  this->refKeypoints.push_back(keypointIndex);
  this->refImages.push_back(image);
}

ObjectPoint::ObjectPoint(float x, float y, float z) :
    coordinates_(x, y, z) {
  Mat gl_coordinates_mat = rotate_x_axis_180 * Mat(coordinates_, false);
  gl_coordinates_mat.copyTo(Mat(gl_coordinates_, false));
}

void ObjectPoint::removeReferencesToImage(shared_ptr<Image> image) {
  int i;
  for (auto ref_image : refImages) {
    if (ref_image == image) {
      refImages.erase(refImages.begin() + i);
      refKeypoints.erase(refKeypoints.begin() + i);
    }
    else
      ++i;
  }
}

void ObjectPoint::recalculateColor() {
  Point3_<uint> sum_colors(0, 0, 0);

  for (int i = 0; i < refImages.size(); ++i) {
    KeyPoint key_point = refImages.at(i)->get_keypoints()->at(refKeypoints.at(i));
    Point3_<uchar> *color = refImages.at(i)->mat_color()->ptr<Point3_<uchar> >(key_point.pt.y, key_point.pt.x);
    sum_colors.x += (int) color->x;
    sum_colors.y += (int) color->y;
    sum_colors.z += (int) color->z;
  }

  color_.x = ((float) sum_colors.z / refImages.size()) / 255;
  color_.y = ((float) sum_colors.y / refImages.size()) / 255;
  color_.z = ((float) sum_colors.x / refImages.size()) / 255;
}
