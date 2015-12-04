//
// Created by joschi on 07.11.15.
//

#include "surffeaturedetector.h"


SURFFeatureDetector::SURFFeatureDetector() : surf(SURF::create(100, 4, 3, true, false)) {
}

void SURFFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints) {
  for (auto image: images) {
    surf->detectAndCompute(*image->mat_grey(), noArray(), *image->get_keypoints(), *image->get_descriptors(),
                           useProvidedKeypoints);
  }
}
