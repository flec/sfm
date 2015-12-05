//
// Created by joschi on 07.11.15.
//

#ifndef SFM_SURFCUDAFEATUREDETECTOR_H
#define SFM_SURFCUDAFEATUREDETECTOR_H

#ifdef USE_CUDA
#include "featuredetector.h"
#include "opencv2/xfeatures2d/cuda.hpp"
#include <opencv2/calib3d.hpp>

using namespace cv::cuda;

class SURFCUDAFeatureDetector : public FeatureDetecter {
private:
  SURF_CUDA surf_cuda;

public:
  SURFCUDAFeatureDetector();

  void detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints = false);

};

#endif // USE_CUDA

#endif //SFM_SURFCUDAFEATUREDETECTOR_H