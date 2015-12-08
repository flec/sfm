/*
* Interface for bundle adjuster
*/

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
