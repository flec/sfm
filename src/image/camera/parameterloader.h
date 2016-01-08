// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_PARAMETERLOADER_H
#define SFM_PARAMETERLOADER_H

#include <opencv2/core/mat.hpp>

using namespace std;
using namespace cv;

/**
 * Class for loading image camera parameters
 */
class ParameterLoader {
public:
  /**
   * Loads the intrinsic camera parameters and the distortion coefficients if available.
   * The files mus be named camera_intrinsic.yaml and camera_distortion.yaml
   *
   * dir_name                 Directory name that contains the files
   * intrinsic                output: intrinsic camera matrix
   * distortion_coefficients  output: camera distortion coefficients
   */
  static void load(const string &dir_path, Mat &intrinsic, Mat &distortion_coefficients);
};
#endif //SFM_PARAMETERLOADER_H
