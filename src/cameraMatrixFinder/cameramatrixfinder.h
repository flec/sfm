/*
* Interface for camera matrix finder
*/

#ifndef SFM_CAMERAMATRIXFINDER_H
#define SFM_CAMERAMATRIXFINDER_H

#pragma once

#include <memory>
#include "image/pair/imagepair.h"

using namespace cv;
using namespace std;

class CameraMatrixFinder
{
public:
  virtual void findCameraMatrix(shared_ptr<ImagePair> &image_pair, Mat& intristic_camera_paramaters) = 0;
private:

};

#endif // SFM_CAMERAMATRIXFINDER_H