// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_FLANNFEATUREMATCHER_H
#define SFM_FLANNFEATUREMATCHER_H

#include "featurematcher.h"
#include <opencv2/features2d.hpp>

class FlannFeatureMatcher : public FeatureMatcher{
private:
  FlannBasedMatcher matcher;
public:
  shared_ptr<ImagePair> matchFeatures(shared_ptr<Image> &image, shared_ptr<Image> &image2);
};


#endif //SFM_FLANNFEATUREMATCHER_H
