// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_SURFFEATUREDETECTOR_H
#define SFM_SURFFEATUREDETECTOR_H

#include "featuredetector.h"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/calib3d.hpp"

using namespace xfeatures2d;

/*
 * Implementation of the SURF feature detector
 */
class SURFFeatureDetector : public FeatureDetecter {
private:
  Ptr<SURF> surf;


public:
  SURFFeatureDetector();

  /**
   * @see FeatureDetecter
   */
  void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false);

};

#endif //SFM_SURFFEATUREDETECTOR_H