//
// Created by joschi on 19.10.15.
//

#ifndef SFM_IMAGELOADER_H
#define SFM_IMAGELOADER_H


#include "image.h"
#include <string>
#include <memory>

using namespace std;

class ImageLoader {
public:
  static vector<shared_ptr<Image>> loadImagesFromDir(string const& dirName);
};


#endif //SFM_IMAGELOADER_H
