//
// Created by marco on 19.11.15.
//

#ifndef SFM_PLYUTIL_H
#define SFM_PLYUTIL_H

#include <iostream>
#include <fstream>
#include <memory>
#include "opencv2/core/core.hpp"
#include "image/objectPoint/objectpoint.h"

using namespace cv;
using namespace std;

class PlyUtil {
public:
  static void write(const string& fileName, const Mat& points3Dh);
  static void write(const string& fileName, const vector<shared_ptr<ObjectPoint>> &objectPoints);
};


#endif //SFM_PLYUTIL_H
