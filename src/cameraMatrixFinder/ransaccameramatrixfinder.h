//
// Created by joschi on 05.11.15.
//

#ifndef SFM_RANSACCAMERAMATRIXFINDER_H
#define SFM_RANSACCAMERAMATRIXFINDER_H

#include "cameramatrixfinder.h"

class RANSACCameraMatrixFinder : public CameraMatrixFinder{
public:
  void findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat& intristic_camera_paramaters);
};


#endif //SFM_RANSACCAMERAMATRIXFINDER_H
