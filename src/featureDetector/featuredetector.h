/*
* Interface for feature detector
*/

#ifndef SFM_FEATUREDETECTOR_H
#define SFM_FEATUREDETECTOR_H

#pragma once

#include <opencv2/core/cvdef.h>
#include "opencv2/core/core.hpp"
#include "image/image.h"
#include <memory>

using namespace cv;
using namespace std;

class FeatureDetecter {
public:
  const static int max_features=5000;

  virtual void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false) = 0;

};

#endif //SFM_FEATUREDETECTOR_H

