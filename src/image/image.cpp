//
// Created by joschi on 19.10.15.
//

#include <opencv2/imgcodecs.hpp>
#include "util/fileutil.h"
#include "image.h"
#include "imageloadexception.h"


Image::Image(string const &file_path, bool const load_color) {
#ifdef DEBUG
  printf("Loading image %s\n", file_path.c_str());
#endif
  this->file_path = FileUtil::getPathName(file_path);
  this->file_name = FileUtil::getFileName(file_path);

  this->mat_grey = imread(file_path, IMREAD_GRAYSCALE);
  if (mat_grey.data == NULL)
    throw ImageLoadException("Image::Image(): loading image failed " + file_path);

  if (load_color)
    this->mat_color = imread(file_path, IMREAD_COLOR);
}

Image::~Image() {
#ifdef DEBUG
  printf("Destructing image %s\n", file_path.c_str());
#endif
}


