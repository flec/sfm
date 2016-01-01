//
// Created by marco on 01.01.16.
//

#ifndef SFM_CORNERMINEIGENVALFEATUREDETECTOR_H
#define SFM_CORNERMINEIGENVALFEATUREDETECTOR_H

#include "opencv2/features2d.hpp"
#include "featuredetector.h"

/*
 * Implementation of the corner minimum eigen value feature detector
 */
class CornerMinEigenValFeatureDetector : public FeatureDetecter {
public:

  /**
   * @see FeatureDetecter
   */
  void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false);

};
#endif //SFM_CORNERMINEIGENVALFEATUREDETECTOR_H
