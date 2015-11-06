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
  feature_detector->detectFeatures(images);
}

void SFMApp::matchFeatures() {
  image_pairs.clear();
  for (unsigned int i = 0; i < images.size(); i++) {
    for (unsigned int j = i + 1; j < images.size(); j++) {
      image_pairs.push_back(feature_matcher->matchFeatures(images.at(i), images.at(j)));
      feature_matcher->filterMatches(image_pairs.back());
    }
  }
}


void SFMApp::findInitialMatrices(shared_ptr<ImagePair> &initial_image_pair, Mat& intristic_camera_paramaters) {
  this->initial_image_pair = initial_image_pair;
  this->intrinsic_camera_parameters = intristic_camera_paramaters;
  cameraMatrixFinder->findCameraMatrix(initial_image_pair, intristic_camera_paramaters);
}


