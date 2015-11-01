//
// Created by joschi on 30.10.15.
//

#ifndef SFM_FLANNFEATUREMATCHER_H
#define SFM_FLANNFEATUREMATCHER_H

#include "featurematcherinterface.h"
#include <image/image.h>
#include <opencv2/features2d.hpp>

class FlannFeatureMatcher : public FeatureMatcherInterface{
private:
  FlannBasedMatcher matcher;
public:
  shared_ptr<FeatureMatches> matchFeatures(shared_ptr<Image> &image, shared_ptr<Image> &image2);
};


#endif //SFM_FLANNFEATUREMATCHER_H
