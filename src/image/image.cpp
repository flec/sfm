// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <opencv2/imgcodecs.hpp>
#include "util/fileutil.h"
#include "image.h"
#include "imageloadexception.h"


Image::Image(string const &file_path, bool const load_color) : camera_(shared_ptr<ImageCamera>(new ImageCamera())) {
#ifdef DEBUG
  printf("Loading image %s\n", file_path.c_str());
#endif
  this->file_path_ = FileUtil::getPathName(file_path);
  this->file_name_ = FileUtil::getFileName(file_path);

  this->mat_grey_ = imread(file_path, IMREAD_GRAYSCALE);
  if (mat_grey_.data == NULL)
    throw ImageLoadException("Image::Image(): loading file as image failed " + file_path);

  if (load_color)
    this->mat_color_ = imread(file_path, IMREAD_COLOR);
}

Image::~Image() {
#ifdef DEBUG
  printf("Destructing image %s\n", file_path_.c_str());
#endif
}

void Image::addObjectPoint(int keypoint_index, shared_ptr<ObjectPoint> point) {
  this->object_points_[keypoint_index] = point;
}

shared_ptr<ObjectPoint> Image::getObjectPoint(int keypoint_index) {
  map<int, shared_ptr<ObjectPoint>>::iterator it = this->object_points_.find(keypoint_index);
  // return null if not found
  if (it == this->object_points_.end()) {
    return nullptr;
  }
  return it->second;
}

void Image::clearObjectPointsAndCamera() {
  object_points_.clear();
  camera_ = shared_ptr<ImageCamera>(new ImageCamera());
}

void Image::removeObjectPoint(int keypoint_index) {
  object_points_.erase(keypoint_index);
}
