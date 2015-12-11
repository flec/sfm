// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "surffeaturedetector.h"

SURFFeatureDetector::SURFFeatureDetector() : surf(SURF::create(100, 4, 3, true, false)) {
}

void SURFFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints) {
  for (auto image: images) {
    surf->detectAndCompute(*image->mat_grey(), noArray(), *image->keypoints(), *image->descriptors(),
                           use_provided_keypoints);
  }
}
