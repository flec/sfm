// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "cameramatrixfinder.h"

void CameraMatrixFinder::removeOutlinerMatches(shared_ptr<ImagePair> &image_pair, Mat &inliners) {
  int count = 0;
  auto i = begin(image_pair->matches);
  while (i != end(image_pair->matches)) {
    if (inliners.at<char>(count++) == 0) {
      i = image_pair->matches.erase(i);
    }
    else
      ++i;
  }
}