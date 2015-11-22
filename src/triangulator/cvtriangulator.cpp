//
// Created by marco on 18.11.15.
//

#include "cvtriangulator.h"
#include <opencv2/calib3d.hpp>
#include "util/plyutil.h"

using namespace std;
using namespace cv;

void CVTriangulator::findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &points3Dh) {
  vector<cv::Point2f> points1;
  vector<cv::Point2f> points2;

  image_pair->getMatches(points1, points2);

  triangulatePoints(image_pair->projection_img1, image_pair->projection_img2,
                    points1, points2, points3Dh);


  // Since it's homogenous (x, y, z, w) coord, divide by w to get (x, y, z, 1)
  points3Dh.row(0) = (points3Dh.row(0) / points3Dh.row(3)) + 0;
  points3Dh.row(1) = (points3Dh.row(1) / points3Dh.row(3)) + 0;
  points3Dh.row(2) = (points3Dh.row(2) / points3Dh.row(3)) + 0;

  PlyUtil::write("/tmp/test.ply", points3Dh);
}