//#include "opencv2/core/core.hpp"
// Created by joschi on 20.10.15.
//


#include "kazefeaturedetector.h"



KAZEFeatureDetector::KAZEFeatureDetector() : kaze(KAZE::create()) {
}

void KAZEFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints) {
  for (auto image: images) {
    image->get_keypoints()->clear();
    image->get_descriptors()->release();
    kaze->detectAndCompute(*image->get_mat_grey(), noArray(), *image->get_keypoints(), *image->get_descriptors(), useProvidedKeypoints);
  }
}