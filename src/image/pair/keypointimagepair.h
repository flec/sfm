// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_KEYPOINTIMAGEPAIR_H
#define SFM_KEYPOINTIMAGEPAIR_H

#include <memory>
#include <opencv2/core/types.hpp>

using namespace std;
using namespace cv;

// forward declaration
class Image;

struct KeyPointImagePair {
public:
  KeyPointImagePair();

  KeyPointImagePair(int keyPointIndex, KeyPoint *keyPoint, shared_ptr<Image> image);

  KeyPointImagePair(int keyPointIndex, shared_ptr<Image> image);

  int keyPointIndex;
  KeyPoint *key_point;
  shared_ptr<Image> image;
};

#endif //SFM_KEYPOINTIMAGEPAIR_H
