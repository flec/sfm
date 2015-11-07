//
// Created by joschi on 07.11.15.
//

#if 0
#ifndef SFM_SIFTFEATUREDETECTOR_H
#define SFM_SIFTFEATUREDETECTOR_H
#include "featuredetector.h"

class SIFTFeatureDetector : public FeatureDetecter {
private:
  Ptr<SIFT> sift;


public:
  SIFTFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);

};


#endif //SFM_SIFTFEATUREDETECTOR_H
#endif