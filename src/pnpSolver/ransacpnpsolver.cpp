//
// Created by marco on 22.11.15.
//

#include <opencv2/calib3d.hpp>
#include "ransacpnpsolver.h"

void RANSACPnPSolver::solve(shared_ptr <ImagePair> &image_pair, Mat &intristic_camera_paramaters) {

  solvePnPRansac(image_pair->pnp_object_points, image_pair->pnp_image_points, intristic_camera_paramaters,
                 noArray(), image_pair->rotation, image_pair->translation);
}