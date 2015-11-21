//
// Created by joschi on 20.11.15.
//

#ifndef SFM_BRISKFEATUREDETECTOR_H
#define SFM_BRISKFEATUREDETECTOR_H


#include <opencv2/features2d.hpp>
#include "featuredetector.h"

class BRISKFeatureDetector : public FeatureDetecter {
private:
  Ptr<BRISK> brisk;


public:
  BRISKFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);

};


#endif //SFM_BRISKFEATUREDETECTOR_H
