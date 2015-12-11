// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "kazefeaturedetector.h"

KAZEFeatureDetector::KAZEFeatureDetector() : kaze(KAZE::create(false,false, 0.000001f,6,6)) {
}

void KAZEFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints) {
  for (auto image: images) {
    kaze->detectAndCompute(*image->mat_grey(), noArray(), *image->get_keypoints(), *image->get_descriptors(), use_provided_keypoints);
  }
}
