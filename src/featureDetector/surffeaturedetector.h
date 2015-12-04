//
// Created by joschi on 07.11.15.
//

#ifndef SFM_SURFFEATUREDETECTOR_H
#define SFM_SURFFEATUREDETECTOR_H
#include "featuredetector.h"
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/calib3d.hpp>

using namespace xfeatures2d;

class SURFFeatureDetector : public FeatureDetecter {
private:
  Ptr<SURF> surf;


public:
  SURFFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);

};


#endif //SFM_SURFFEATUREDETECTOR_H