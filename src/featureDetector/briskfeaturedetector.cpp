//
// Created by joschi on 20.11.15.
//

#include "briskfeaturedetector.h"



BRISKFeatureDetector::BRISKFeatureDetector() : brisk(BRISK::create()) {
}

void BRISKFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints) {
  for (auto image: images) {
    brisk->detectAndCompute(*image->get_mat_grey(), noArray(), *image->get_keypoints(), *image->get_descriptors(), useProvidedKeypoints);
  }
}
