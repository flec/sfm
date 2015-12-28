// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_BFFEATUREMATCHER_H
#define SFM_BFFEATUREMATCHER_H

#include "featurematcher.h"
#include "opencv2/features2d.hpp"

/**
 * Implmentation of the brute-force feature matching algorithm.
 */
class BFFeatureMatcher : public FeatureMatcher {
private:
  BFMatcher matcher;
public:
  /**
   * @see FeatureMatcher
   */
  shared_ptr<ImagePair> matchFeatures(shared_ptr<Image> &image, shared_ptr<Image> &image2);
};


#endif //SFM_BFFEATUREMATCHER_H
