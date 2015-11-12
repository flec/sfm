//
// Created by joschi on 07.11.15.
//

#ifndef SFM_MATRIXUTIL_H
#define SFM_MATRIXUTIL_H

#include "opencv2/core/core.hpp"
#include <iostream>
using namespace cv;
using namespace std;

class MatrixUtil {
public:
  static Mat_<double> getEulerAnglesByRotationMatrix(Mat_<double> &r);
};


#endif //SFM_MATRIXUTIL_H
