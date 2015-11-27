//
// Created by joschi on 27.11.15.
//

#include "camera.h"

void Camera::set_rotation_translation(const Mat_<double> &rotation, const Mat_<double> &translation) {
  rotation_translation_ = (Mat_<double>(3, 4) <<
                           rotation(0, 0), rotation(0, 1), rotation(0, 2), translation(0),
      rotation(1, 0), rotation(1, 1), rotation(1, 2), translation(1),
      rotation(2, 0), rotation(2, 1), rotation(2, 2), translation(2));
}