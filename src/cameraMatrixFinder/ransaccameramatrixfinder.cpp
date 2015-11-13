//
// Created by joschi on 05.11.15.
//

#include <iostream>
#include <opencv2/calib3d.hpp>
#include "ransaccameramatrixfinder.h"
#include <math.h>

void RANSACCameraMatrixFinder::findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat& intristic_camera_paramaters){
  vector<Point2f> points_img1;
  vector<Point2f> points_img2;

  for(auto match:image_pair->matches)
  {
    //-- Get the keypoints from the good matches
    points_img1.push_back(image_pair->image1->get_keypoints()->at(match.queryIdx).pt);
    points_img2.push_back(image_pair->image2->get_keypoints()->at(match.trainIdx).pt);
  }


  Mat inliners;

  image_pair->fundamental = findFundamentalMat(points_img1, points_img2, CV_FM_RANSAC, 2, 0.999, inliners);
  image_pair->essential = intristic_camera_paramaters.t() * image_pair->fundamental * intristic_camera_paramaters;

  // Extract transaltion and rotation
  SVD svd(image_pair->essential,SVD::MODIFY_A);
  Mat svd_u = svd.u;
  Mat svd_vt = svd.vt;
  Mat svd_w = svd.w;
  Matx33d W(0,-1,0,//HZ 9.13
            1,0,0,
            0,0,1);

  image_pair->rotation = svd_u * Mat(W).t() * svd_vt;
  image_pair->translation = svd_u.col(2);

//  Mat F = findFundamentalMat(points_img1, points_img2, CV_FM_8POINT, 2, 0.9999, inliners);
//  Mat_<double> E = intristic_camera_paramaters.t() * F * intristic_camera_paramaters;

//  // Extract transaltion and rotation
//  SVD svd2(E,SVD::MODIFY_A);
//  Mat svd_u2 = svd2.u;
//  Mat svd_vt2 = svd2.vt;
//  Mat svd_w2 = svd2.w;
//  Matx33d W2(0,-1,0,//HZ 9.13
//            1,0,0,
//            0,0,1);
//
//
//  Mat_<double> R= svd_u2 * Mat(W2).t() * svd_vt2;
//  Mat_<double> T=svd_u2.col(2);
//  cout<<intristic_camera_paramaters<<endl;
//  cout<<F<<endl<<endl;
//  // F should be around
//  // -60.9979e-009     5.8124e-006     547.8079e-006
//  // 11.0044e-006      709.6751e-009  -263.0490e-003
//  // -1.7015e-003      253.8168e-003   933.1865e-003
//  cout<<R<<endl<<endl;
//  // R should be around
//  // 996.5006e-003   -27.9893e-003    78.7595e-003
//  // 27.8333e-003    999.6078e-003    3.0784e-003
//  // -78.8148e-003   -875.4670e-006   996.8889e-003
//  cout<<T<<endl;
}
