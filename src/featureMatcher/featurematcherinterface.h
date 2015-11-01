/*
* Interface for feature matcher
*/

#pragma once

#include <opencv2/core/cvdef.h>
#include "opencv2/core/core.hpp"
#include "image/matches/featurematches.h"
#include "image/image.h"
#include <memory>

using namespace std;
using namespace cv;

class FeatureMatcherInterface
{
public:
  virtual shared_ptr<FeatureMatches> matchFeatures(shared_ptr<Image> &image, shared_ptr<Image> &image2) = 0;

};
