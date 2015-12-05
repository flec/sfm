//
// Created by joschi on 07.11.15.
//

#ifdef USE_CUDA

#include <iostream>
#include "surfcudafeaturedetector.h"


SURFCUDAFeatureDetector::SURFCUDAFeatureDetector() : surf_cuda(SURF_CUDA((100, 4, 3, true, false))) {
}

void SURFCUDAFeatureDetector::detectFeatures(vector<shared_ptr<Image>> &images, bool useProvidedKeypoints) {
  cv::cuda::printShortCudaDeviceInfo(cv::cuda::getDevice());

  // Detect keypoints of images in a parallel fashion
#pragma omp for
  for (int i = 0; i< images.size();++i) {
    GpuMat keypoints_GPU, descriptors_GPU;

    // Upload image to GPU
    GpuMat img_GPU;
    img_GPU.upload(*images.at(i)->mat_grey());
    surf_cuda(img_GPU, GpuMat(), keypoints_GPU, descriptors_GPU, useProvidedKeypoints);

    // download results from GPU
    surf_cuda.downloadKeypoints(keypoints_GPU, *images.at(i)->get_keypoints());
    Mat(descriptors_GPU).copyTo(*images.at(i)->get_descriptors());
    //surf_cuda.downloadDescriptors(descriptors_GPU, *image->get_descriptors());
  }
}

#endif // USE_CUDA