//
// Created by marco on 18.11.15.
//

#include "cvtriangulator.h"
#include <opencv2/calib3d.hpp>
#include "util/plyutil.h"

using namespace std;
using namespace cv;

void CVTriangulator::findPoints3D(shared_ptr<ImagePair> &image_pair, vector <Point3f> &points3D) {
  Mat mat_points3d;
  triangulatePoints(image_pair->projection_img1, image_pair->projection_img2,
                    image_pair->triangulation_points1, image_pair->triangulation_points2, mat_points3d);

// Since it's homogenous (x, y, z, w) coord, divide by w to get (x, y, z, 1)
  mat_points3d.row(0) = (mat_points3d.row(0) / mat_points3d.row(3)) + 0;
  mat_points3d.row(1) = (mat_points3d.row(1) / mat_points3d.row(3)) + 0;
  mat_points3d.row(2) = (mat_points3d.row(2) / mat_points3d.row(3)) + 0;

  for(int i=0; i<mat_points3d.cols; i++) {
    points3D.push_back(Point3f(mat_points3d.at<float>(0,i), mat_points3d.at<float>(1,i), mat_points3d.at<float>(2,i)));
  }

}