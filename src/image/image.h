//
// Created by joschi on 19.10.15.
//

#ifndef SFM_IMAGE_H
#define SFM_IMAGE_H

#include <opencv2/core/mat.hpp>
#include <map>
#include <image/camera/imagecamera.h>
#include "objectPoint/objectpoint.h"

using namespace cv;
using namespace std;


class Image {
  friend class TestCube;
private:
  vector<KeyPoint> keypoints_;

  Mat mat_color_;
  Mat mat_grey_;

  string file_name_;
  string file_path_;

  // map with keypoint index and opject point
  map<int, shared_ptr<ObjectPoint>> object_points_;

  Image() { };

  shared_ptr<ImageCamera> camera_;

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

  shared_ptr<ImageCamera> camera(){return camera_;};

};


#endif //SFM_IMAGE_H
