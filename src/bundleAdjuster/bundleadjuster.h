// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <vector>
#include <memory>
#include "image/image.h"
#include "image/pair/imagepair.h"
#include "image/objectPoint/objectpoint.h"

class BundleAdjuster {
public:
  virtual void adjust(Mat intrinsicCameraParams, vector<shared_ptr<ObjectPoint>> &objectPoints,
                      vector<shared_ptr<Image>> &images) = 0;
};
