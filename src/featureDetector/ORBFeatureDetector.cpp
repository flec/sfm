//
// Created by joschi on 20.10.15.
//


#include "ORBFeatureDetector.h"


void ORBFeatureDetector::detectFeatures(InputArray image, CV_OUT vector<KeyPoint> &keypoints, OutputArray descriptors,
                                        bool useProvidedKeypoints) {
  orb->detectAndCompute(image, noArray(), keypoints, descriptors, useProvidedKeypoints);
}

ORBFeatureDetector::ORBFeatureDetector() : orb(ORB::create()) {
}
