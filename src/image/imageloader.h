// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_IMAGELOADER_H
#define SFM_IMAGELOADER_H


#include "image.h"
#include <string>
#include <memory>

using namespace std;

class ImageLoader {
public:
  static vector<shared_ptr<Image>> loadImagesFromDir(string const &dirName);

private:
  static vector<string> read_directory(const string &path = string());
};


#endif //SFM_IMAGELOADER_H
