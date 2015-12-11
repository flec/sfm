// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_TESTCUBE_H
#define SFM_TESTCUBE_H

#include <opencv2/calib3d.hpp>
#include <vector>
#include <memory>
#include "image/image.h"
#include "image/pair/imagepair.h"

using namespace cv;
using namespace std;

class TestCube {
private:

  static void setKeypointsImg1(vector<KeyPoint> &keyPoints);
  static void setKeypointsImg2(vector<KeyPoint> &keyPoints);
  static void setKeypointsImg3(vector<KeyPoint> &keyPoints);
  static void setMatches(int num, vector<DMatch> &matches);

public:
  static void setPairs(vector<shared_ptr<ImagePair>> &pairs);

  static Mat_<double> getIntrinsicMatrix();
};

#endif //SFM_TESTCUBE_H
