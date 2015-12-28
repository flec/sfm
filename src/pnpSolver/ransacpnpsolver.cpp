// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <opencv2/calib3d.hpp>
#include <iostream>
#include "ransacpnpsolver.h"

void RANSACPnPSolver::solve(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) {
  // calculate estimate based on the first image
  Mat rot_estimate = image_pair->image1->camera()->extrinsic_rotation() * image_pair->rotation;
  Mat trans_estimate = image_pair->image1->camera()->extrinsic_translation() + image_pair->translation;

  Mat rvec;
  Mat tvec;
  Mat rot;

  // convert estimate for use in solvePnPRansac
  Rodrigues(rot_estimate, rvec);
  tvec = trans_estimate;

  if (image_pair->pnp_object_points.size() < 3) {
    cerr << "Aborting PnP solving (less than 3 points given). Likely bad things to come" << endl;
    return;
  }

  // estimate pose of camera in second image
  solvePnPRansac(image_pair->pnp_object_points, image_pair->pnp_image_points, intristic_camera_paramaters,
                 noArray(), rvec, tvec, true, 100, 2.0, 0.99, noArray());

  // convert rotation to 3x3 matrix
  Rodrigues(rvec, rot);
  // set estimated pose in camera of second image
  image_pair->image2->camera()->set_extrinsic(rot, tvec);
}
