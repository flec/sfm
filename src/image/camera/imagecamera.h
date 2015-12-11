// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_CAMERA_H
#define SFM_CAMERA_H

#include "opencv2/core/mat.hpp"
#include <memory>

using namespace std;
using namespace cv;

/*
 * Represents a camera that sees an Image.
 */
struct ImageCamera {
private:
  // Projection matrix
  Mat_<float> projection_;

  // Camera position as rotation and translation [R|t] in object coordinates (relative to the camera)
  Mat_<double> extrinsic_;

  // Camera position as rotation and translation [R|t] in world coordinates (relative to the world/center)
  Mat_<double> position_;

  // Camera position rotated by 180 degrees around the X axis. This is used, to get the point cloud not bottom-up, as
  //   - OpenCV: x goes top-down, y left to right
  //   - OpenGL: x(-axis) goes bottom-up, y left to right
  Mat_<double> gl_position_;

  // Rotation matrix used to rotate a point by 180 degrees around the X-axis
  static Mat_<double> rotate_x_axis_180;

public:

  /**
   * Set the extrinsic rotation and translation. The parameters must be in object coordinates.
   *
   * rotation     The rotation of the camera in object coordinates.
   * translation  The translation of the camera in object coordinates.
   */
  void set_extrinsic(const Mat_<double> &rotation, const Mat_<double> &translation);

  /**
   * Set rotation and translation to identity matrix.
   */
  void set_extrinsic();

  //
  // getters / setters
  //

  Mat_<float> *projection() {return &projection_;}

  Mat_<double> *extrinsic() { return &extrinsic_; }

  Mat_<double> *gl_rotation_translation() { return &gl_position_; }

  Mat_<double> extrinsic_rotation() { return extrinsic_.data==NULL?Mat_<double>(): extrinsic_(Rect(0, 0, 3, 3)); }

  Mat_<double> position_rotation() { return position_.data==NULL?Mat_<double>(): position_(Rect(0, 0, 3, 3)); }

  Mat_<double> gl_rotation() { return gl_position_(Rect(0, 0, 3, 3)); }

  Mat_<double> extrinsic_translation() { return extrinsic_.data==NULL?Mat_<double>(): extrinsic_(Rect(3, 0, 1, 3)); }

  Mat_<double> position_translation() { return position_.data==NULL?Mat_<double>(): position_(Rect(3, 0, 1, 3)); }

  Mat_<double> gl_translation() { return gl_position_(Rect(3, 0, 1, 3)); }
};


#endif //SFM_CAMERA_H
