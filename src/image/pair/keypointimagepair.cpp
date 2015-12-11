// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "keypointimagepair.h"
#include "image/image.h"

KeyPointImagePair::KeyPointImagePair() { }

KeyPointImagePair::KeyPointImagePair(int keyPointIndex, KeyPoint *keyPoint, shared_ptr<Image> image) :
    keyPointIndex(keyPointIndex), key_point(keyPoint), image(image) {

}

KeyPointImagePair::KeyPointImagePair(int keyPointIndex, shared_ptr<Image> image) :
    keyPointIndex(keyPointIndex), image(image) {
  key_point = &image->get_keypoints()->at(keyPointIndex);
}