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

/**
 *
 */
struct KeyPointImagePair {
private:
  int key_point_index_;
  shared_ptr<Image> image_;
public:
  KeyPointImagePair();
  KeyPointImagePair(int key_point_index, shared_ptr<Image> image);
  KeyPoint *getKeyPoint();
  int key_point_index(){ return key_point_index_;}
  shared_ptr<Image> image() { return image_;}
};

#endif //SFM_KEYPOINTIMAGEPAIR_H
