//
// Created by joschi on 20.10.15.
//

#ifndef SFM_ORBFEATUREDETECTOR_H
#define SFM_ORBFEATUREDETECTOR_H

#include <opencv2/features2d.hpp>
#include "featuredetectorinterface.h"

class ORBFeatureDetector : FeatureDetectorInterface {

  ORBFeatureDetector();

  void detectFeatures(const _InputArray &image, vector<KeyPoint> &keypoints, const _OutputArray &descriptors,
                      bool useProvidedKeypoints = false);

private:
  Ptr<ORB> orb;
};


#endif //SFM_ORBFEATUREDETECTOR_H
