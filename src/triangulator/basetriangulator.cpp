//
// Created by marco on 18.11.15.
//

#include "basetriangulator.h"
#include <opencv2/calib3d.hpp>
#include "util/plyutil.h"

using namespace std;
using namespace cv;

void BaseTriangulator::findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &points3Dh) {
  vector<cv::Point2f> points1;
  vector<cv::Point2f> points2;

  this->getMatchedPoints(image_pair, &points1, &points2);

  triangulatePoints(image_pair->projection_img1, image_pair->projection_img2,
                    points1, points2, points3Dh);


  // Since it's homogenous (x, y, z, w) coord, divide by w to get (x, y, z, 1)
  //points3Dh.row(0) = (points3Dh.row(0) / points3Dh.row(3)) + 0;
  //points3Dh.row(1) = (points3Dh.row(1) / points3Dh.row(3)) + 0;
  //points3Dh.row(2) = (points3Dh.row(2) / points3Dh.row(3)) + 0;

  PlyUtil::write("/tmp/test.ply", points3Dh);
}

void BaseTriangulator::getMatchedPoints(shared_ptr<ImagePair> &image_pair, vector<Point2f> *points1,
                                        vector<Point2f> *points2) {
  vector<KeyPoint> *keypoints1 = image_pair->image1->get_keypoints();
  vector<KeyPoint> *keypoints2 = image_pair->image2->get_keypoints();

  vector<DMatch>::iterator it;
  for (it = image_pair->matches.begin(); it != image_pair->matches.end(); it++) {
    points1->push_back(keypoints1->at(it->queryIdx).pt);
    points2->push_back(keypoints2->at(it->trainIdx).pt);
  }
}