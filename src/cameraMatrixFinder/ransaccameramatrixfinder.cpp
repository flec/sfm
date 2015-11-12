//
// Created by joschi on 05.11.15.
//

#include <iostream>
#include <opencv2/calib3d.hpp>
#include "ransaccameramatrixfinder.h"

void RANSACCameraMatrixFinder::findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat& intristic_camera_paramaters){
  vector<Point2f> points_img1;
  vector<Point2f> points_img2;

  for(auto match:image_pair->matches)
  {
    //-- Get the keypoints from the good matches
    points_img1.push_back(image_pair->image1->get_keypoints()->at(match.queryIdx).pt);
    points_img2.push_back(image_pair->image2->get_keypoints()->at(match.trainIdx).pt);
  }

  image_pair->fundamental = findFundamentalMat(points_img1, points_img2, FM_RANSAC, 2, 0.9999);
  image_pair->essential = intristic_camera_paramaters.t() * image_pair->fundamental * intristic_camera_paramaters;

  // Extract transaltion and rotation
  SVD svd(image_pair->essential,SVD::MODIFY_A);
  Mat svd_u = svd.u;
  Mat svd_vt = svd.vt;
  Mat svd_w = svd.w;
  Matx33d W(0,-1,0,//HZ 9.13
            1,0,0,
            0,0,1);

  image_pair->rotation = svd_u * Mat(W) * svd_vt;
  image_pair->translation = svd_u.col(2);
}
