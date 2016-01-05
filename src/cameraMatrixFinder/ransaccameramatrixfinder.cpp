// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iostream>
#include <opencv2/calib3d.hpp>
#include "ransaccameramatrixfinder.h"
#include <opencv2/highgui.hpp>

void RANSACCameraMatrixFinder::findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters) {
  vector<Point2f> points_img1;
  vector<Point2f> points_img2;

  // get keypoints from matches as vector<Point2f>
  image_pair->getMatches(points_img1, points_img2);

  // Mask with inliers
  Mat inliers;

  // create camera center point
  Point2d camera_center(intrinsic_camera_parameters.at<double>(0, 2), intrinsic_camera_parameters.at<double>(1, 2));

  // compute the essential matrix directly
  image_pair->essential = findEssentialMat(points_img1, points_img2, intrinsic_camera_parameters.at<double>(0, 0),
  camera_center, RANSAC, 0.999, 1.0, inliers);

  // get rotation and translation matrix - cheirality check is done inside this function
  // computing the rot and trans matrix could also be done by using SVD, but then the cheirality needs to be done
  // by "hand"
  recoverPose(image_pair->essential, points_img1, points_img2, image_pair->rotation, image_pair->translation,
              intrinsic_camera_parameters.at<double>(0, 0), camera_center, inliers);

  removeOutlierMatches(image_pair, inliers);
}
