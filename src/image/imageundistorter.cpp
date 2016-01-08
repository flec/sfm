//
// Created by marco on 07.01.16.
//

#include <opencv2/imgproc.hpp>
#include <iostream>
#include "imageundistorter.h"

void ImageUndistorter::undistort(vector<shared_ptr <Image>> images, Mat &intrinsic,
                                 Mat &distortion_coefficients) {

#ifdef DEBUG
  cout<<"Undistorting images with matrix: "<<distortion_coefficients<<endl;
#endif
  Mat image_output;
  for (auto image : images) {
    // undistort color image
    cv::undistort(*image->mat_color(), image_output, intrinsic, distortion_coefficients);
    image->set_mat_color(image_output);

    // undistort greyscale image
    cv::undistort(*image->mat_grey(), image_output, intrinsic, distortion_coefficients);
    image->set_mat_grey(image_output);
  }
}