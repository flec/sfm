//
// Created by marco on 22.11.15.
//

#include <opencv2/calib3d.hpp>
#include "ransacpnpsolver.h"

void RANSACPnPSolver::solve(shared_ptr <ImagePair> &image_pair, Mat &intristic_camera_paramaters) {
  Mat rvec;
  Mat tvec;
  Mat rot;
  Mat trans;

  solvePnPRansac(image_pair->pnp_object_points, image_pair->pnp_image_points, intristic_camera_paramaters,
                 noArray(), rvec, tvec, false,  100, 8, 0.99, noArray());

  Rodrigues(rvec, rot);
  rot = rot.t();
  trans = -rot * tvec;
  image_pair->image2->camera()->set_rotation_translation(rot, trans);
}