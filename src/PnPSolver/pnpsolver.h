//
// Created by marco on 22.11.15.
//

#ifndef SFM_PNPSOLVER_H
#define SFM_PNPSOLVER_H

#include "image/pair/imagepair.h"

class PnPSolver {
public:
  void solve(shared_ptr<ImagePair> &image_pair);
};
#endif //SFM_PNPSOLVER_H
