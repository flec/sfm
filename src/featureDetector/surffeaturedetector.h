// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

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