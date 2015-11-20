//
// Created by marco on 18.11.15.
//

#ifndef SFM_PROJECTIONMATRIXFINDER_H
#define SFM_PROJECTIONMATRIXFINDER_H


#include <memory>
#include "image/pair/imagepair.h"

class ProjectionMatrixFinder {
public:
  virtual void findProjectionMatrix(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) = 0;
};

#endif //SFM_PROJECTIONMATRIXFINDER_H