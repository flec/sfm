//
// Created by marco on 22.11.15.
//

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
