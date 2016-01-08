// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <opencv2/imgproc.hpp>
#include "cornermineigenvalfeaturedetector.h"

const int CornerMinEigenValFeatureDetector::MAX_CORNERS = 5000;
const double CornerMinEigenValFeatureDetector::QUALITY_LEVEL = 0.001;
const double CornerMinEigenValFeatureDetector::MIN_DISTANCE = 10;

void CornerMinEigenValFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images,
                                                      bool use_provided_keypoints) {
  vector<Point2f> corners;
  for (auto image: images) {
#ifdef DEBUG
    cout<<"Detecting corner minimal eigen value features on image "<<image->file_name()<<endl;
#endif
    goodFeaturesToTrack(*image->mat_grey(), corners, MAX_CORNERS, QUALITY_LEVEL, MIN_DISTANCE);
    for (auto corner: corners) {
      image->keypoints()->push_back(KeyPoint(corner, 1));
    }
  }
}