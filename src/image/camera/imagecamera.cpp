//
// Created by joschi on 27.11.15.
//

#include <src/image/objectPoint/objectpoint.h>
#include "imagecamera.h"

Mat_<double> ImageCamera::rotate_x_axis_180 = (Mat_<double>(3, 3) << 1, 0, 0, 0, -1, 0, 0, 0, -1);

void ImageCamera::set_rotation_translation(const Mat_<double> &rotation, const Mat_<double> &translation) {
  rotation_translation_ = (Mat_<double>(3, 4) <<
                           rotation(0, 0), rotation(0, 1), rotation(0, 2), translation(0),
      rotation(1, 0), rotation(1, 1), rotation(1, 2), translation(1),
      rotation(2, 0), rotation(2, 1), rotation(2, 2), translation(2));

  Mat_<double> new_gl_translation = rotate_x_axis_180 * translation;
  Mat_<double> new_gl_rotation = rotate_x_axis_180 * rotation;
  gl_rotation_translation_ = (Mat_<double>(3, 4) <<
      new_gl_rotation(0, 0), new_gl_rotation(0, 1), new_gl_rotation(0, 2), new_gl_translation(0),
      new_gl_rotation(1, 0), new_gl_rotation(1, 1), new_gl_rotation(1, 2), new_gl_translation(1),
      new_gl_rotation(2, 0), new_gl_rotation(2, 1), new_gl_rotation(2, 2), new_gl_translation(2));
}

// sets roation and transaltion to identity matrix
void ImageCamera::set_rotation_translation() {
  rotation_translation_ = Mat::eye(3, 4, CV_64FC1);
  gl_rotation_translation_ = rotation_translation_;
}