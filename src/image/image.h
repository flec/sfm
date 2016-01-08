// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_IMAGE_H
#define SFM_IMAGE_H

#include "opencv2/core/mat.hpp"
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
  // The image itself in color
  Mat mat_color_;

  // The image itself in gray scaled
  Mat mat_grey_;

  // The name of the image
  string file_name_;

  // Directory that contains the image
  string file_path_;

  // vector containing keypoints of the features
  vector<KeyPoint> keypoints_;

  // cv::Mat containing the descriptors of the features
  Mat descriptors_;

  // Camera that sees this image
  shared_ptr<ImageCamera> camera_;

  // A map containing all object points that are based on a keypoint of this image
  // The key is the keypoint index and the value the opject point
  map<int, shared_ptr<ObjectPoint>> object_points_;

  Image() { };

public:

  /**
   * Initialize an image. It will load the image from disk and load its content to mat_color_ and mat_grey_
   *
   * file_path    Path and name to the image
   * load_color   Load mat_grey AND mat_color
   *
   * throws   ImageLoadException    if the image cannot be loaded (ie the file_path is not a path to an image)
   */
  Image(string const &file_path, bool const load_color = true);

  /**
   * Initialize an image that has already been loaded. From the colored image a greyscale image will be created as well.
   *
   * file_path  Files name used as identifier
   * image      The image as Mat
   */
  Image(const string &file_path, Mat image);

  /**
   * Unload image from memory before deconstruction
   */
  ~Image();

  /**
   * Add an object point that is based on a keypoint of this image
   *
   * keypoint_index   index of the keypoint
   * point            the ObjectPoint to add
   */
  void addObjectPoint(int keypoint_index, shared_ptr<ObjectPoint> point);

  /**
   * remove a reference to an ObjectPoint that this image has
   *
   * keypoint_index   index of the keypoint that has a reference to the ObjectPoint. This reference will be removed.
   */
  void removeObjectPoint(int keypoint_index);

  /**
   * Get the ObjectPoint that is based on a certain keypoint
   *
   * keypoint_index   index of the keypoint
   */
  shared_ptr<ObjectPoint> getObjectPoint(int keypoint_index);

  void clearObjectPointsAndCamera();

  //
  // getters/setters
  //

  Mat *mat_color() { return (mat_color_.data != NULL) ? &mat_color_ : &mat_grey_; }

  Mat *mat_grey() { return &mat_grey_; }

  void set_mat_color(Mat image) {image.copyTo(mat_color_);}

  void set_mat_grey(Mat image) {image.copyTo(mat_grey_);}

  string file_name() const { return file_name_; }

  string file_path() const { return file_path_; }

  vector<KeyPoint> *keypoints() { return &keypoints_; }

  Mat *descriptors() { return &descriptors_; }

  map<int, shared_ptr<ObjectPoint>> *object_points() { return &object_points_; };

  shared_ptr<ImageCamera> camera() { return camera_; };
};


#endif //SFM_IMAGE_H
