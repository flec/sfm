//
// Created by marco on 18.11.15.
//

#ifndef SFM_CVPROJECTIONMATRIXFINDER_H
#define SFM_CVPROJECTIONMATRIXFINDER_H

#include "projectionmatrixfinder.h"

class CvProjectionMatrixFinder : public ProjectionMatrixFinder {
public:
  void findProjectionMatrix(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters);
};

#endif //SFM_CVPROJECTIONMATRIXFINDER_H
