// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "keypointimagepair.h"
#include "image/image.h"

KeyPointImagePair::KeyPointImagePair() { }

KeyPointImagePair::KeyPointImagePair(int key_point_index, shared_ptr<Image> image) :
    key_point_index_(key_point_index), image_(image) {
}

KeyPoint* KeyPointImagePair::getKeyPoint() {
  return &image_->keypoints()->at(key_point_index_);
}