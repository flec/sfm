//#include "opencv2/core/core.hpp"
// Created by joschi on 20.10.15.
//


#include "orbfeaturedetector.h"



ORBFeatureDetector::ORBFeatureDetector() : orb(ORB::create(FeatureDetecter::max_features)) {
}

void ORBFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints) {
  for (auto image: images) {
    orb->detectAndCompute(*image->mat_grey(), noArray(), *image->get_keypoints(), *image->get_descriptors(), useProvidedKeypoints);
  }
}