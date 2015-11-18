//
// Created by joschi on 30.10.15.
//

#ifndef SFM_IMAGEPAIR_H
#define SFM_IMAGEPAIR_H

#include <memory>
#include <vector>
#include <image/image.h>

using namespace std;

struct ImagePair {
public:
  shared_ptr<Image> image1;
  shared_ptr<Image> image2;

  vector<DMatch> matches;
  Mat_<double> rotation;
  Mat_<double> translation;
  Mat_<double> fundamental;
  Mat_<double> essential;
};


#endif //SFM_IMAGEPAIR_H
