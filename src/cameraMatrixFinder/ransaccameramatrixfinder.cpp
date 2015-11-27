//
// Created by joschi on 05.11.15.
//

#include <iostream>
#include <opencv2/calib3d.hpp>
#include "ransaccameramatrixfinder.h"
#include <opencv2/highgui.hpp>

void RANSACCameraMatrixFinder::findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) {
  vector<Point2f> points_img1;
  vector<Point2f> points_img2;

  // get keypoints_ from good matches
  image_pair->getMatches(points_img1, points_img2);

  // Mask with inliners
  Mat inliners;

  // find the fundamental matrix
  image_pair->fundamental = findFundamentalMat(points_img1, points_img2, CV_FM_RANSAC, 2, 0.9999, inliners);

  // compute the essential matrix - this could also be done by using the function findEssentialMat
  image_pair->essential = intristic_camera_paramaters.t() * image_pair->fundamental *
                          intristic_camera_paramaters;

  Point2d camera_center(intristic_camera_paramaters.at<double>(0, 2), intristic_camera_paramaters.at<double>(1, 2));

  // get rotation and translation matrix - cheirality check is done inside this function
  // computing the rot and trans matrix could also be done by using SVD, but then the cheirality needs to be done
  // by "hand"
  recoverPose(image_pair->essential, points_img1, points_img2, image_pair->rotation, image_pair->translation,
              intristic_camera_paramaters.at<double>(0, 0), camera_center, inliners);

  // see http://stackoverflow.com/a/14543277
  image_pair->rotation = image_pair->rotation.t();
  image_pair->translation = image_pair->rotation*-image_pair->translation;

  removeOutlinerMatches(image_pair, inliners);


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
