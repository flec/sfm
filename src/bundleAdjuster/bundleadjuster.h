// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_BUNDLEADJUSTER_H
#define SFM_BUNDLEADJUSTER_H

#include <vector>
#include <memory>
#include "image/image.h"
#include "image/pair/imagepair.h"
#include "image/objectPoint/objectpoint.h"

/**
 * Interface for performing bundle adjustment.
 * Bundle adjustment is used to adjust the object points and the camera positions
 */
class BundleAdjuster {
public:
  /**
   * Performs bundle adjustment
   *
   * intrinsicCameraParams  intrinsic camera parameters
   * objectPoints           object points in the 3D space
   * images                 corresponding images to the object points
   */
  virtual void adjust(Mat intrinsic_camera_params, vector<shared_ptr<ObjectPoint>> &object_points,
                      vector<shared_ptr<Image>> &images) = 0;
};

#endif SFM_BUNDLEADJUSTER_H
