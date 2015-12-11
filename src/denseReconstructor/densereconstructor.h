// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_DENSERECONSTRUCTOR_H
#define SFM_DENSERECONSTRUCTOR_H

#include "image/pair/imagepair.h"

class DenseReconstructor {
public:
  virtual void reconstruct(vector<shared_ptr<ImagePair>> &image_pairs) = 0;
};

#endif //SFM_DENSERECONSTRUCTOR_H
