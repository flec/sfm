// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_PNPSOLVER_H
#define SFM_PNPSOLVER_H

#include "image/pair/imagepair.h"

class PnPSolver {
public:
  virtual void solve(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) = 0;
};

#endif //SFM_PNPSOLVER_H
