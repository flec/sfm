// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifdef USE_CUDA

#include <iostream>
#include "surfcudafeaturedetector.h"


SURFCUDAFeatureDetector::SURFCUDAFeatureDetector() : surf_cuda(SURF_CUDA((100, 4, 3, true, false))) {
}

void SURFCUDAFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints) {
#ifdef DEBUG
  printShortCudaDeviceInfo(cv::cuda::getDevice());
#endif

  // Detect keypoints of images in a parallel fashion
#pragma omp for
  for (int i = 0; i< images.size();++i) {
    GpuMat keypoints_GPU, descriptors_GPU;

    // Upload image to GPU
    GpuMat img_GPU;
    img_GPU.upload(*images.at(i)->mat_grey());

    // compute the descriptors and keypoints on the GPU
    surf_cuda(img_GPU, GpuMat(), keypoints_GPU, descriptors_GPU, use_provided_keypoints);

    // download results from GPU
    surf_cuda.downloadKeypoints(keypoints_GPU, *images.at(i)->get_keypoints());
    Mat(descriptors_GPU).copyTo(*images.at(i)->get_descriptors());
  }
}

#endif // USE_CUDA
