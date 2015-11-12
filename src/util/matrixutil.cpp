//
// Created by joschi on 07.11.15.
//

#include "matrixutil.h"
#include <math.h>

Mat_<double> MatrixUtil::getEulerAnglesByRotationMatrix(Mat_<double> &r) {
  double Ry1 = -1 * asin(r.at<double>(3, 1));
  double Ry2 = M_PI - Ry1;
  double Rx1 = atan2(r.at<double>(3, 2) / cos(Ry1), r.at<double>(3, 3) / cos(Ry1));
  double Rx2 = atan2(r.at<double>(3, 2) / cos(Ry2), r.at<double>(3, 3) / cos(Ry2));
  double Rz1 = atan2(r.at<double>(2, 1) / cos(Ry1), r.at<double>(1, 1) / cos(Ry1));
  double Rz2 = atan2(r.at<double>(2, 1) / cos(Ry2), r.at<double>(1, 1) / cos(Ry2));

  Mat_<double> angles1 = (Mat_<double>(3, 1) << Rx1, Ry1, Rz1);
  Mat_<double> angles2 = (Mat_<double>(3, 1) << Rx2, Ry2, Rz2);
  cout<<(angles1/ M_PI * 180)<<endl;
  cout<<(angles2/ M_PI * 180)<<endl;
  return angles1;
}