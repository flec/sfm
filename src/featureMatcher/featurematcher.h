// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_FEATUREMATCHER_H
#define SFM_FEATUREMATCHER_H

#include "opencv2/core/cvdef.h"
#include "opencv2/core/core.hpp"
#include "image/pair/imagepair.h"
#include "image/image.h"
#include <memory>
#include <iostream>

using namespace std;
using namespace cv;

/*
 * Interface for matching features between two images. The matches saved in a ImagePair can then be used
 * to find camera matrices @see CameraMatrixFinder.
 */
class FeatureMatcher {
public:
  /**
   * Match features between two images. Thus the descriptors of both images are matched by an algorithm against each
   * other. The result is a list that matches one keypoint in image1 to another in image2.
   *
   * image1   First image
   * image2   Second image
   * returns  an ImagePair, that will contain the computed matches between the two images afterwards.
   */
  virtual shared_ptr<ImagePair> matchFeatures(shared_ptr<Image> &image1, shared_ptr<Image> &image2) = 0;

  /**
   * Filter matches out of an image pair that have a to long distance. This can be useful to speed-up the
   * camera matrix finding. But on the other hand it can be dangerous, as the maximum allowed distance is computed
   * relatively. Thus one very very good match would cause that other good matches are filterd out.
   *
   * image_pair       Filter matches of this ImagePair
   * min_dist_factor  Factor for computing the maximum allowed distance.
   */
  void filterMatches(shared_ptr<ImagePair> &image_pair, double min_dist_factor = 6.5);

};


#endif //SFM_FEATUREMATCHER_H
