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
 * Represents a key point index with corresponding image
 */
struct KeyPointImagePair {
private:
  /**
   * index of the referenced key point
   */
  int key_point_index_;
  /**
   * Corresponding image
   */
  shared_ptr<Image> image_;
public:
  /**
   * Default constructor
   */
  KeyPointImagePair();
  /**
   * Constructor that initializes all fields
   * key_point_index  index of the key point in the image
   * image            corresponding image where the key point can be found by index
   */
  KeyPointImagePair(int key_point_index, shared_ptr<Image> image);
  /**
   * Getter for key point
   */
  KeyPoint *getKeyPoint();
  /**
   * Getter for key point index
   */
  int key_point_index(){ return key_point_index_;}
  /**
   * Getter for image
   */
  shared_ptr<Image> image() { return image_;}
};

#endif //SFM_KEYPOINTIMAGEPAIR_H
