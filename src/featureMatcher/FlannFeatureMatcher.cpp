//
// Created by joschi on 30.10.15.
//

#include "FlannFeatureMatcher.h"

shared_ptr<FeatureMatches> FlannFeatureMatcher::matchFeatures(shared_ptr<Image> &image1, shared_ptr<Image> &image2){
  shared_ptr<FeatureMatches> matches(new FeatureMatches());
  matches->image1 = image1;
  matches->image2 = image2;

  if(image1->get_descriptors()->type()!=CV_32F)
    image1->get_descriptors()->convertTo(*image1->get_descriptors(), CV_32F);
  if(image2->get_descriptors()->type()!=CV_32F)
    image2->get_descriptors()->convertTo(*image2->get_descriptors(), CV_32F);

  matcher.match( *image1->get_descriptors(), *image2->get_descriptors(), matches->matches );
  return matches;
}