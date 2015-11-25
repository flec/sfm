//
// Created by joschi on 19.10.15.
//

#ifndef SFM_IMAGE_H
#define SFM_IMAGE_H

#include <opencv2/core/mat.hpp>
#include <map>
#include "objectPoint/objectpoint.h"

using namespace cv;
using namespace std;

class Image {
private:
  vector<KeyPoint> keypoints_;

  Mat mat_color_;
  Mat mat_grey_;

  string file_name_;
  string file_path_;

  // map with keypoint index and opject point
  map<int, shared_ptr<ObjectPoint>> object_points_;

  // matrix with camera rotation and translation [R|t] relative to the initial image
  Mat_<double> rotation_translation_;

  Image() { };

public:
  Mat descriptors;

  Image(string const &file_path, bool const load_color = true);

  ~Image();

  Mat *mat_color() { return (mat_color_.data != NULL) ? &mat_color_ : &mat_grey_; }

  Mat *mat_grey() { return &mat_grey_; }

  string file_name() const { return file_name_; }

  string file_path() const { return file_path_; }

  vector<KeyPoint> *get_keypoints() { return &keypoints_; }

  Mat *get_descriptors() { return &descriptors; }

  map<int, shared_ptr<ObjectPoint>> *object_points() { return &object_points_; };

  void addObjectPoint(int keypointIndex, shared_ptr<ObjectPoint> point);

  shared_ptr<ObjectPoint> getObjectPoint(int keypointIndex);

  Mat_<double> *rotation_translation() { return &rotation_translation_; }

  void set_rotation_translation(const Mat_<double> &rotation, const Mat_<double> &translation);

  // sets roation and transaltion to identity matrix
  void set_rotation_translation();
};


#endif //SFM_IMAGE_H
