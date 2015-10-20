//
// Created by joschi on 19.10.15.
//

#include <image/imageloader.h>
#include "sfmapp.h"

void SFMApp::detectFeatures() {

}

SFMApp::SFMApp(string const &images_dir) {
  images = ImageLoader::loadImagesFromDir(images_dir);
}

void SFMApp::unloadImages() {
  images.clear();
}
