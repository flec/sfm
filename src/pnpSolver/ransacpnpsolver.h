// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_RANSACPNPSOLVER_H
#define SFM_RANSACPNPSOLVER_H

#include "pnpsolver.h"

using namespace cv;
using namespace std;
/**
 * Implementation of the perspective-n-point solver using a RANSAC approach to minimize outliners
 */
class RANSACPnPSolver : public PnPSolver {
public:
  /**
   * @see PnPSolver
   */
  void solve(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters);
};
#endif //SFM_RANSACPNPSOLVER_H
