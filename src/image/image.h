// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_IMAGE_H
#define SFM_IMAGE_H

#include <opencv2/core/mat.hpp>
#include <map>
#include "objectPoint/objectpoint.h"
#include "camera/imagecamera.h"

using namespace cv;
using namespace std;

/**
 * Struct that represents an image. It all data that is associated with an image.
 */
struct Image {
  friend class TestCube;

private:
  // vector containing keypoints of the features
  vector<KeyPoint> keypoints_;

  // cv::Mat containing the descriptors of the features
  Mat descriptors_;

  // The image itself in color
  Mat mat_color_;

  // The image itself in gray scaled
  Mat mat_grey_;

  // The name of the image
  string file_name_;

  // Directory that contains the image
  string file_path_;

  // map with keypoint index and opject point
  map<int, shared_ptr<ObjectPoint>> object_points_;

  // Camera that sees this image
  shared_ptr<ImageCamera> camera_;

  Image() { };

public:

  /**
   * Initialize an image. It will load the image from disk and load its content to mat_color_ and mat_grey_
   *
   * file_path    Path and name to the image
   * load_color   Load mat_grey AND mat_color
   */
  Image(string const &file_path, bool const load_color = true);

  ~Image();

  map<int, shared_ptr<ObjectPoint>> *object_points() { return &object_points_; };

  void addObjectPoint(int keypointIndex, shared_ptr<ObjectPoint> point);

  void removeObjectPoint(int keypointIndex);

  shared_ptr<ObjectPoint> getObjectPoint(int keypointIndex);

  shared_ptr<ImageCamera> camera() { return camera_; };

  void clearObjectPointsAndCamera();

  // Getters/Setters

  Mat *mat_color() { return (mat_color_.data != NULL) ? &mat_color_ : &mat_grey_; }

  Mat *mat_grey() { return &mat_grey_; }

  string file_name() const { return file_name_; }

  string file_path() const { return file_path_; }

  vector<KeyPoint> *keypoints() { return &keypoints_; }

  Mat *descriptors() { return &descriptors_; }

};


#endif //SFM_IMAGE_H
