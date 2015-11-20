//
// Created by marco on 20.11.15.
//

#ifndef SFM_TESTCUBE_H
#define SFM_TESTCUBE_H

#include <opencv2/calib3d.hpp>
#include <vector>

using namespace cv;
using namespace std;

class TestCube {
public:
  static void getMatches(vector<Point2f> *points1, vector<Point2f> *points2);
};
#endif //SFM_TESTCUBE_H
