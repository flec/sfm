// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "orbfeaturedetector.h"

ORBFeatureDetector::ORBFeatureDetector() : orb(ORB::create(FeatureDetecter::max_features)) {
}

void ORBFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints) {
  for (auto image: images) {
#ifdef DEBUG
    cout<<"Detecting ORB features on image "<<image->file_name()<<endl;
#endif
    orb->detectAndCompute(*image->mat_grey(), noArray(), *image->keypoints(), *image->descriptors(), use_provided_keypoints);
  }
}
