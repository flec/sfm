//
// Created by marco on 22.11.15.
//

#ifndef SFM_DENSERECONSTRUCTOR_H
#define SFM_DENSERECONSTRUCTOR_H

#include "image/pair/imagepair.h"

class DenseReconstructor {
public:
  virtual void reconstruct(vector<shared_ptr<ImagePair>> &image_pairs) = 0;
};

#endif //SFM_DENSERECONSTRUCTOR_H
