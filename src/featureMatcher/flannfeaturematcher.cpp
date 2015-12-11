// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "flannfeaturematcher.h"

shared_ptr<ImagePair> FlannFeatureMatcher::matchFeatures(shared_ptr<Image> &image1, shared_ptr<Image> &image2){
  shared_ptr<ImagePair> image_pair(new ImagePair());
  image_pair->image1 = image1;
  image_pair->image2 = image2;

  if(image1->get_descriptors()->type()!=CV_32F)
    image1->get_descriptors()->convertTo(*image1->get_descriptors(), CV_32F);
  if(image2->get_descriptors()->type()!=CV_32F)
    image2->get_descriptors()->convertTo(*image2->get_descriptors(), CV_32F);

  matcher.match( *image1->get_descriptors(), *image2->get_descriptors(), image_pair->matches );
  return image_pair;
}