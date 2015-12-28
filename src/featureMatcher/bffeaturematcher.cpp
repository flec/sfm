// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "bffeaturematcher.h"

shared_ptr<ImagePair> BFFeatureMatcher::matchFeatures(shared_ptr<Image> &image1, shared_ptr<Image> &image2) {
  shared_ptr<ImagePair> image_pair(new ImagePair());
  image_pair->image1 = image1;
  image_pair->image2 = image2;

  // convert descriptors to CV_32F, if they are not
  // CV_32F features are required by the bf matcher
  if (image1->descriptors()->type() != CV_32F)
    image1->descriptors()->convertTo(*image1->descriptors(), CV_32F);
  if (image2->descriptors()->type() != CV_32F)
    image2->descriptors()->convertTo(*image2->descriptors(), CV_32F);

  matcher.match(*image1->descriptors(), *image2->descriptors(), image_pair->matches);
  return image_pair;
}