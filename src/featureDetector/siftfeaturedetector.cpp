// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "siftfeaturedetector.h"

SIFTFeatureDetector::SIFTFeatureDetector() : sift(SIFT::create(FeatureDetecter::max_features,3,0.04,10)) {
}

void SIFTFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints) {
  for (auto image: images) {
    sift->detectAndCompute(*image->mat_grey(), noArray(), *image->keypoints(), *image->descriptors(), use_provided_keypoints);
  }
}
