/*
* Interface for feature detector
*/

#pragma once

#include <opencv2/core/cvdef.h>
#include "opencv2/core/core.hpp"
#include "image/image.h"
#include <memory>

using namespace cv;
using namespace std;

class FeatureDetectorInterface {
public:
  virtual void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false) = 0;

};
