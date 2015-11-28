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
  // extrinsic matrix with camera rotation and translation [R|t]
  Mat_<double> extrinsic_;

  // cameras position as rotation and translation [R|t] in world coordinates
  Mat_<double> position_;

  // rotated by 180? around the X axis
  // OpenCV: x goes top-down, y left to right
  // OpenGL: x(-axis) goes bottom-up, y left to right
  Mat_<double> gl_position_;

  static Mat_<double> rotate_x_axis_180;

public:

  Mat_<double> *extrinsic() { return &extrinsic_; }

  Mat_<double> *gl_rotation_translation() { return &gl_position_; }

  Mat_<double> extrinsic_rotation() { return extrinsic_.data==NULL?Mat_<double>(): extrinsic_(Rect(0, 0, 3, 3)); }

  Mat_<double> position_rotation() { return position_.data==NULL?Mat_<double>(): position_(Rect(0, 0, 3, 3)); }

  Mat_<double> gl_rotation() { return gl_position_(Rect(0, 0, 3, 3)); }

  Mat_<double> extrinsic_translation() { return extrinsic_.data==NULL?Mat_<double>(): extrinsic_(Rect(3, 0, 1, 3)); }

  Mat_<double> position_translation() { return position_.data==NULL?Mat_<double>(): position_(Rect(3, 0, 1, 3)); }

  Mat_<double> gl_translation() { return gl_position_(Rect(3, 0, 1, 3)); }

  void set_extrinsic(const Mat_<double> &rotation, const Mat_<double> &translation);

  // sets rotation and translation to identity matrix
  void set_extrinsic();

};


#endif //SFM_CAMERA_H
