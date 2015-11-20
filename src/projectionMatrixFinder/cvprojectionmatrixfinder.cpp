//
// Created by marco on 18.11.15.
//

#include "cvprojectionmatrixfinder.h"
#include <opencv2/calib3d.hpp>

void CvProjectionMatrixFinder::findProjectionMatrix(shared_ptr<ImagePair> &image_pair,
                                                    Mat &intristic_camera_paramaters) {

  Mat D1 = Mat::zeros(1, 4, CV_32F);
  Mat D2 = Mat::zeros(1, 4, CV_32F);
  Mat Q;
  Size imgSize = image_pair->image1->get_mat_grey()->size();
  stereoRectify(intristic_camera_paramaters, D1, intristic_camera_paramaters, D2,
                imgSize, image_pair->rotation, image_pair->translation,
                image_pair->rotation_rect_img1, image_pair->rotation_rect_img2,
                image_pair->projection_img1, image_pair->projection_img2, Q);
}