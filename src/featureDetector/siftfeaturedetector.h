//
// Created by joschi on 07.11.15.
//

#ifndef SFM_SIFTFEATUREDETECTOR_H
#define SFM_SIFTFEATUREDETECTOR_H
#include "featuredetector.h"
#include <opencv2/xfeatures2d.hpp>

using namespace xfeatures2d;

class SIFTFeatureDetector : public FeatureDetecter {
private:
  Ptr<SIFT> sift;


public:
  SIFTFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);

};


#endif //SFM_SIFTFEATUREDETECTOR_H