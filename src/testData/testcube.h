//
// Created by marco on 20.11.15.
//

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

  static void setKeypointsPair1(vector<KeyPoint> &keyPoints1, vector<KeyPoint> &keyPoints2);
  static void setKeypointsPair2(vector<KeyPoint> &keyPoints1, vector<KeyPoint> &keyPoints2);
  static void setMatches(int num, vector<DMatch> &matches);

public:
  static shared_ptr<ImagePair> getPair1();

  static shared_ptr<ImagePair> getPair2();

  static Mat_<double> getIntrinsicMatrix();
};

#endif //SFM_TESTCUBE_H
