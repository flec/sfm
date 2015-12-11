// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_FEATUREDETECTOR_H
#define SFM_FEATUREDETECTOR_H

#include <opencv2/core/cvdef.h>
#include "opencv2/core/core.hpp"
#include "image/image.h"
#include <memory>

using namespace cv;
using namespace std;

/*
 * Interface for detecting image features. Responsibility of a FeatureDetecter is to detect and describe features
 * in an image. Those features can then be matched between two images @see FeatureMatcher.
 */
class FeatureDetecter {
public:
  // Detect a maximum of max_features, if supported by the implementing feature detector.
  const static int max_features = 5000;

  /**
   * Detect the features for each image. The result being keypoints and descriptors are save into the Image itself.
   * Thus Image->descriptors and Image->keypoints will be overriden.
   *
   * images                 Detect the features for this list of images.
   * use_provided_keypoints Use the provided keypoints and therefore update only the descriptors.
   */
  virtual void detectFeatures(vector<shared_ptr<Image>> &images, bool use_provided_keypoints = false) = 0;

};

#endif //SFM_FEATUREDETECTOR_H

