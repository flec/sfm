// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_KAZEFEATUREDETECTOR_H
#define SFM_KAZEFEATUREDETECTOR_H

#include "opencv2/features2d.hpp"
#include "featuredetector.h"

/*
 * Implementation of the KAZE feature detector
 */
class KAZEFeatureDetector : public FeatureDetecter {
private:
  Ptr<KAZE> kaze;

public:
  KAZEFeatureDetector();

  /**
   * @see FeatureDetecter
   */
  void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false);
};


#endif //SFM_KAZEFEATUREDETECTOR_H
