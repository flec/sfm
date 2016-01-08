// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <opencv2/imgproc.hpp>
#include "parameterloader.h"

void ParameterLoader::load(const string &dir_path, Mat &intrinsic,
                          Mat &distortion_coefficients) {

  // load intrinsic parameters if available
  string intrinsic_file = dir_path + "/camera_intrinsic.yaml";
  if (FILE *file = fopen(intrinsic_file.c_str(), "r")) {
    fclose(file);
    FileStorage fs(intrinsic_file, FileStorage::READ);
    fs["mat1"] >> intrinsic;

    // load distortion coefficients if available but only if intrinsic parameters are available
    string distortion_file = dir_path + "/camera_distortion.yaml";
    if (FILE *file = fopen(distortion_file.c_str(), "r")) {
      fclose(file);
      FileStorage fs(distortion_file, FileStorage::READ);
      fs["mat1"] >> distortion_coefficients;
    }
  }
}