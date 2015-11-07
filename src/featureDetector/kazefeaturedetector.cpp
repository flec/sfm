//#include "opencv2/core/core.hpp"
// Created by joschi on 20.10.15.
//


#include "kazefeaturedetector.h"



KAZEFeatureDetector::KAZEFeatureDetector() : kaze(KAZE::create(FeatureDetecter::max_features)) {
}

void KAZEFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints) {
  for (auto image: images) {
    kaze->detectAndCompute(*image->get_mat_grey(), noArray(), *image->get_keypoints(), *image->get_descriptors(), useProvidedKeypoints);
  }
}