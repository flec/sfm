// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_DENSERECONSTRUCTOR_H_H
#define SFM_DENSERECONSTRUCTOR_H_H

#include "densereconstructor.h"

using namespace cv;
using namespace std;

class PatchDenseReconstructor : public DenseReconstructor {
public:
  void reconstruct(vector<shared_ptr<ImagePair>> &image_pairs);
};
#endif //SFM_DENSERECONSTRUCTOR_H_H
