//
// Created by joschi on 19.10.15.
//

#ifndef SFM_SFMAPP_H
#define SFM_SFMAPP_H

#include "image/image.h"

using namespace std;

class SFMApp {
private:
  vector<Image> images;
public:
  SFMApp(string const& images_dir);
  void detectFeatures();
};


#endif //SFM_SFMAPP_H
