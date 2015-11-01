//
// Created by joschi on 20.10.15.
//

#ifndef SFM_ORBFEATUREDETECTOR_H
#define SFM_ORBFEATUREDETECTOR_H

#include <opencv2/features2d.hpp>
#include "featuredetectorinterface.h"

class ORBFeatureDetector : public FeatureDetectorInterface {
private:
  Ptr<ORB> orb;

public:
  ORBFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);
};


#endif //SFM_ORBFEATUREDETECTOR_H
