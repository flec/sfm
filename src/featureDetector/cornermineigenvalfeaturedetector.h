// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_CORNERMINEIGENVALFEATUREDETECTOR_H
#define SFM_CORNERMINEIGENVALFEATUREDETECTOR_H

#include "opencv2/features2d.hpp"
#include "featuredetector.h"

/*
 * Implementation of the corner minimum eigen value feature detector
 */
class CornerMinEigenValFeatureDetector : public FeatureDetecter {
private:
  /**
   * Detector parameters
   */
  static const int MAX_CORNERS;
  static const double QUALITY_LEVEL;
  static const double MIN_DISTANCE;

public:

  /**
   * @see FeatureDetecter
   */
  void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false);

};
#endif //SFM_CORNERMINEIGENVALFEATUREDETECTOR_H
