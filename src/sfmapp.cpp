//
// Created by joschi on 19.10.15.
//

#include <image/imageloader.h>
#include "sfmapp.h"

SFMApp* SFMApp::getInstance() {
  if(!instance)
    instance = new SFMApp();
  return instance;
}

SFMApp* SFMApp::instance = 0;

void SFMApp::loadImages(string const &images_dir) {
  images = ImageLoader::loadImagesFromDir(images_dir);
}

void SFMApp::unloadImages() {
  images.clear();
}

void SFMApp::detectFeatures() {
  featureDetector->detectFeatures(images);
}

void SFMApp::matchFeatures() {
  image_pairs.clear();
  for (unsigned int i = 0; i < images.size(); i++) {
    for (unsigned int j = i + 1; j < images.size(); j++) {
      image_pairs.push_back(featureMatcher->matchFeatures(images.at(i), images.at(j)));
      featureMatcher->filterMatches(image_pairs.back());
    }
  }
}


void SFMApp::findMatrices() {
  for(auto image_pair : image_pairs) {
    cameraMatrixFinder->findCameraMatrix(image_pair);
  }
}


