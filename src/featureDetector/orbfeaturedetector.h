// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_ORBFEATUREDETECTOR_H
#define SFM_ORBFEATUREDETECTOR_H

#include "opencv2/features2d.hpp"
#include "featuredetector.h"

/*
 * Implementation of the ORB feature detector
 */
class ORBFeatureDetector : public FeatureDetecter {
private:
  Ptr<ORB> orb;

public:
  ORBFeatureDetector();

  /**
   * @see FeatureDetecter
   */
  void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false);
};


#endif //SFM_ORBFEATUREDETECTOR_H
