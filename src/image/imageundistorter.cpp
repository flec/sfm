//
// Created by marco on 07.01.16.
//

#include <opencv2/imgproc.hpp>
#include "imageundistorter.h"

void ImageUndistorter::undistort(vector<shared_ptr <Image>> images, Mat &intrinsic,
                                 Mat &distortion_coefficients) {

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