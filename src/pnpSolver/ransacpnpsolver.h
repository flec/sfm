//
// Created by marco on 22.11.15.
//

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
