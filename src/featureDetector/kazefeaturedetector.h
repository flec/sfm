//
// Created by joschi on 20.10.15.
//

#ifndef SFM_KAZEFEATUREDETECTOR_H
#define SFM_KAZEFEATUREDETECTOR_H

#include <opencv2/features2d.hpp>
#include "featuredetector.h"

class KAZEFeatureDetector : public FeatureDetecter {
private:
  Ptr<KAZE> kaze;

public:
  KAZEFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);
};


#endif //SFM_KAZEFEATUREDETECTOR_H
