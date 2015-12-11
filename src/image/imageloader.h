// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_IMAGELOADER_H
#define SFM_IMAGELOADER_H


#include "image.h"
#include <string>
#include <memory>

using namespace std;

/**
 * Class for bulk loading Images from a directory.
 */
class ImageLoader {
public:

  /**
   * Load all images from a directory.
   *
   * dir_name   The directory to load the images from
   * returns    A vector containing all loaded Images
   */
  static vector<shared_ptr<Image>> loadImagesFromDir(string const &dir_name);

private:

  /**
   * Get all file names that are inside a directory sorted by ASCII table.
   * Check the value of the global variable errno after calling this function for errors.
   *
   * path     The path to the directory
   * returns  A vector containing all file names of the directory
   */
  static vector<string> read_directory(const string &path = string());
};


#endif //SFM_IMAGELOADER_H
