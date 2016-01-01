//
// Created by marco on 01.01.16.
//

#include <opencv2/imgproc.hpp>
#include "cornermineigenvalfeaturedetector.h"

void CornerMinEigenValFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images,
                                                      bool use_provided_keypoints) {
  int maxCorners = 5000;
  double quality = 0.001;
  double minDistance = 10;

  vector<Point2f> corners;

  for (auto image: images) {
    goodFeaturesToTrack(*image->mat_grey(), corners, maxCorners, quality, minDistance);
    for (auto corner: corners) {
      image->keypoints()->push_back(KeyPoint(corner, 1));
    }
  }
}