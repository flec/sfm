//
// Created by marco on 19.11.15.
//

#ifndef SFM_PLYUTIL_H
#define SFM_PLYUTIL_H

#include <iostream>
#include <fstream>
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

class PlyUtil {
public:
  static void write(const string& filename, const Mat& points3Dh);

};


#endif //SFM_PLYUTIL_H
