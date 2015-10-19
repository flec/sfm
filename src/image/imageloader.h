//
// Created by joschi on 19.10.15.
//

#ifndef SFM_IMAGELOADER_H
#define SFM_IMAGELOADER_H


#include "image.h"
#include <string>

using namespace std;

class ImageLoader {
public:
  static vector<Image> loadImagesFromDir(string const& dirName);
};


#endif //SFM_IMAGELOADER_H
