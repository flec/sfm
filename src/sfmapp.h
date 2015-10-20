//
// Created by joschi on 19.10.15.
//

#ifndef SFM_SFMAPP_H
#define SFM_SFMAPP_H

#include "image/image.h"
#include <memory>

using namespace std;

class SFMApp {

public:
  vector<shared_ptr<Image>> images;

  std::vector<std::vector<KeyPoint>> keypoints;

  std::vector<Mat> descriptors;

  SFMApp(string const &images_dir);

  void detectFeatures();

  void unloadImages();
};


#endif //SFM_SFMAPP_H
