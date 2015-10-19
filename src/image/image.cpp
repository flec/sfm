//
// Created by joschi on 19.10.15.
//

#include <opencv2/imgcodecs.hpp>
#include "util/fileutil.h"
#include "image.h"

Image::Image(string const &file_path) {
  Image(file_path, false);
}

Image::Image(string const &file_path, bool const only_grey) {
  this->file_path = file_path;
  this->file_name = FileUtil::getPathName(file_path);
  this->mat_grey = imread(file_path, IMREAD_GRAYSCALE);
  this->mat_grey = imread(file_path, IMREAD_COLOR);
}

Image::~Image() {}


