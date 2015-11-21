//
// Created by joschi on 30.10.15.
//

#ifndef SFM_IMAGEPAIR_H
#define SFM_IMAGEPAIR_H

#include <memory>
#include <vector>
#include <image/image.h>
#include <map>

using namespace std;

class ImagePair {
public:
  shared_ptr<Image> image1;
  shared_ptr<Image> image2;

  vector<DMatch> matches;
  Mat_<double> rotation;
  Mat_<double> translation;
  Mat_<double> fundamental;
  Mat_<double> essential;

  // Projection matrices
  Mat_<double> projection_img1;
  Mat_<double> projection_img2;
  // Rectified rotation matrices
  Mat_<double> rotation_rect_img1;
  Mat_<double> rotation_rect_img2;

  void getMatches(vector<Point2f> &points1, vector<Point2f> &points2);
private:
  vector<Point2f> matches1;
  vector<Point2f> matches2;
};


#endif //SFM_IMAGEPAIR_H
