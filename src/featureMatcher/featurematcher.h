/*
* Interface for feature matcher
*/

#ifndef SFM_FEATUREMATCHER_H
#define SFM_FEATUREMATCHER_H

#pragma once

#include <opencv2/core/cvdef.h>
#include "opencv2/core/core.hpp"
#include "image/pair/imagepair.h"
#include "image/image.h"
#include <memory>
#include <iostream>

using namespace std;
using namespace cv;

class FeatureMatcher {
public:
  virtual shared_ptr<ImagePair> matchFeatures(shared_ptr<Image> &image, shared_ptr<Image> &image2) = 0;

  void filterMatches(shared_ptr<ImagePair> &image_pair, double min_dist_factor = 5);

};


#endif //SFM_FEATUREMATCHER_H
