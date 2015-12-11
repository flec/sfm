// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_SIFTFEATUREDETECTOR_H
#define SFM_SIFTFEATUREDETECTOR_H

#include "featuredetector.h"
#include "opencv2/xfeatures2d.hpp"

using namespace xfeatures2d;

/*
 * Implementation of the SIFT feature detector
 */
class SIFTFeatureDetector : public FeatureDetecter {
private:
  Ptr<SIFT> sift;

public:
  SIFTFeatureDetector();

  /**
   * @see FeatureDetecter
   */
  void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false);

};


#endif //SFM_SIFTFEATUREDETECTOR_H