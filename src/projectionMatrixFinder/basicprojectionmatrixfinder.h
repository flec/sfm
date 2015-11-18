//
// Created by marco on 18.11.15.
//

#ifndef SFM_BASICPROJECTIONMATRIXFINDER_H
#define SFM_BASICPROJECTIONMATRIXFINDER_H

#include "projectionmatrixfinder.h"

class BasicProjectionMatrixFinder : public ProjectionMatrixFinder {
public:
  void findProjectionMatrix(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters);
};

#endif //SFM_BASICPROJECTIONMATRIXFINDER_H
