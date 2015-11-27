//
// Created by joschi on 27.11.15.
//

#ifndef SFM_CAMERA_H
#define SFM_CAMERA_H

#include <opencv2/core/mat.hpp>
#include <memory>

using namespace std;
using namespace cv;

struct ImageCamera {
private:
  // matrix with camera rotation and translation [R|t] relative to the initial image
  Mat_<double> rotation_translation_;

  // rotated by 180? around the X axis
  // OpenCV: x goes top-down, y left to right
  // OpenGL: x(-axis) goes bottom-up, y left to right
  Mat_<double> gl_rotation_translation_;

  static Mat_<double> rotate_x_axis_180;

public:

  Mat_<double> *rotation_translation() { return &rotation_translation_; }

  Mat_<double> *gl_rotation_translation() { return &gl_rotation_translation_; }

  Mat_<double> rotation() { return rotation_translation_.data==NULL?Mat_<double>():rotation_translation_(Rect(0, 0, 3, 3)); }

  Mat_<double> gl_rotation() { return gl_rotation_translation_(Rect(0, 0, 3, 3)); }

  Mat_<double> translation() { return rotation_translation_.data==NULL?Mat_<double>():rotation_translation_(Rect(3, 0, 1, 3)); }

  Mat_<double> gl_translation() { return gl_rotation_translation_(Rect(3, 0, 1, 3)); }

  void set_rotation_translation(const Mat_<double> &rotation, const Mat_<double> &translation);

  // sets roation and transaltion to identity matrix
  void set_rotation_translation();

};


#endif //SFM_CAMERA_H
