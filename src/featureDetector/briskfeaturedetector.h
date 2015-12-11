// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_BRISKFEATUREDETECTOR_H
#define SFM_BRISKFEATUREDETECTOR_H

#include "opencv2/features2d.hpp"
#include "featuredetector.h"

/*
 * Implementation of the BRISK feature detector
 */
class BRISKFeatureDetector : public FeatureDetecter {
private:
  Ptr<BRISK> brisk;

public:
  BRISKFeatureDetector();

  /**
   * @see FeatureDetecter
   */
  void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false);

};

#endif //SFM_BRISKFEATUREDETECTOR_H
