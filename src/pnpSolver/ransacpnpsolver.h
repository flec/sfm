// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_RANSACPNPSOLVER_H
#define SFM_RANSACPNPSOLVER_H

#include "pnpsolver.h"

using namespace cv;
using namespace std;

class RANSACPnPSolver : public PnPSolver {
public:
  void solve(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters);
};
#endif //SFM_RANSACPNPSOLVER_H
