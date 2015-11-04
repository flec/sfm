//
// Created by joschi on 20.10.15.
//

#ifndef SFM_ORBFEATUREDETECTOR_H
#define SFM_ORBFEATUREDETECTOR_H

#include <opencv2/features2d.hpp>
#include "featuredetector.h"

class ORBFeatureDetector : public FeatureDetecter {
private:
  Ptr<ORB> orb;


public:
  ORBFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);
};


#endif //SFM_ORBFEATUREDETECTOR_H
