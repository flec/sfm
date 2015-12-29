// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_PLYUTIL_H
#define SFM_PLYUTIL_H

#include <iostream>
#include <fstream>
#include <memory>
#include "opencv2/core/core.hpp"
#include "image/objectPoint/objectpoint.h"

using namespace cv;
using namespace std;

/**
 * Utility functions for .ply files
 */
class PlyUtil {
public:
  /**
   * Writes 3D points to a file with the given name
   *
   * file_name      file path including path
   * object_points  3d points
   */
  static void write(const string &file_name, const vector<shared_ptr<ObjectPoint>> &object_points);
};


#endif //SFM_PLYUTIL_H
