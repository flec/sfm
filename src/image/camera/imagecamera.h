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


public:

  Mat_<double> *rotation_translation() { return &rotation_translation_; }

  Mat_<double> rotation() { return rotation_translation_(Rect(0, 0, 3, 3)); }

  Mat_<double> translation() { return rotation_translation_(Rect(3, 0, 1, 3)); }

  void set_rotation_translation(const Mat_<double> &rotation, const Mat_<double> &translation);

  // sets roation and transaltion to identity matrix
  void set_rotation_translation(){
    rotation_translation_ = Mat::eye(3, 4, CV_64FC1);
  }

};


#endif //SFM_CAMERA_H
