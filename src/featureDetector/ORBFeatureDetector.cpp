//
// Created by joschi on 20.10.15.
//


#include "ORBFeatureDetector.h"



ORBFeatureDetector::ORBFeatureDetector() : orb(ORB::create(40)) {
}

void ORBFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints) {
  for (auto image: images) {
    orb->detectAndCompute(*image->get_mat_grey(), noArray(), *image->get_keypoints(), *image->get_descriptors(), useProvidedKeypoints);
  }
}
