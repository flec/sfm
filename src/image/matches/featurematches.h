//
// Created by joschi on 30.10.15.
//

#ifndef SFM_FEATUREMATCH_H
#define SFM_FEATUREMATCH_H

#include <memory>
#include <vector>
#include <image/image.h>

using namespace std;

struct FeatureMatches {
public:
  shared_ptr<Image> image1;
  shared_ptr<Image> image2;

  vector<DMatch> matches;
};


#endif //SFM_FEATUREMATCH_H
