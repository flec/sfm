/*
* Interface for feature matcher
*/

#pragma once

#include <opencv2/core/cvdef.h>
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

class FeatureDetectorInterface {
public:
  virtual void detectFeatures(const _InputArray &image, vector<KeyPoint> &keypoints, const _OutputArray &descriptors,
                              bool useProvidedKeypoints = false) const = 0;


};
