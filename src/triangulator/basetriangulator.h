//
// Created by marco on 18.11.15.
//

#ifndef SFM_BASETRIANGULATOR_H
#define SFM_BASETRIANGULATOR_H

#include "triangulator.h"

class BaseTriangulator : public Triangulator {
public:
  void findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &points3Dh);

private:
  void getMatchedPoints(shared_ptr<ImagePair> &image_pair, vector<Point2f> *points1, vector<Point2f> *points2);
};
#endif //SFM_BASETRIANGULATOR_H
