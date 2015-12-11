// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <src/image/objectPoint/objectpoint.h>
#include "imagecamera.h"

Mat_<double> ImageCamera::rotate_x_axis_180 = (Mat_<double>(3, 3) << 1, 0, 0, 0, -1, 0, 0, 0, -1);

void ImageCamera::set_extrinsic(const Mat_<double> &rotation, const Mat_<double> &translation) {
  // set extrinsic matrix
  extrinsic_ = (Mat_<double>(3, 4) <<
                rotation(0, 0), rotation(0, 1), rotation(0, 2), translation(0),
      rotation(1, 0), rotation(1, 1), rotation(1, 2), translation(1),
      rotation(2, 0), rotation(2, 1), rotation(2, 2), translation(2));

  // set position matrix
  Mat_<double> pos_rotation = rotation.t();
  Mat_<double> pos_translation = -pos_rotation * translation;
  position_ = (Mat_<double>(3, 4) <<
                pos_rotation(0, 0), pos_rotation(0, 1), pos_rotation(0, 2), pos_translation(0),
      pos_rotation(1, 0), pos_rotation(1, 1), pos_rotation(1, 2), pos_translation(1),
      pos_rotation(2, 0), pos_rotation(2, 1), pos_rotation(2, 2), pos_translation(2));

  // set gl position matrix
  Mat_<double> new_gl_translation = rotate_x_axis_180 * pos_translation;
  Mat_<double> new_gl_rotation = rotate_x_axis_180 * pos_rotation;
  gl_position_ = (Mat_<double>(3, 4) <<
                  new_gl_rotation(0, 0), new_gl_rotation(0, 1), new_gl_rotation(0, 2), new_gl_translation(0),
      new_gl_rotation(1, 0), new_gl_rotation(1, 1), new_gl_rotation(1, 2), new_gl_translation(1),
      new_gl_rotation(2, 0), new_gl_rotation(2, 1), new_gl_rotation(2, 2), new_gl_translation(2));
}

// sets roation and transaltion to identity matrix
void ImageCamera::set_extrinsic() {
  extrinsic_ = Mat::eye(3, 4, CV_64FC1);
  position_ = extrinsic_;
  gl_position_ = extrinsic_;
}