// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "featurematcher.h"

void FeatureMatcher::filterMatches(shared_ptr<ImagePair> &image_pair, double min_dist_factor) {
#ifdef DEBUG
  signed int matches_before = image_pair->matches.size();
#endif
  double min_dist = DBL_MAX;

  // calc min distance between keypoints_
  for (auto match : image_pair->matches)
    if (match.distance < min_dist) min_dist = match.distance;

  // erase bad pairs
  auto i = begin(image_pair->matches);
  auto allowed_dist = max(min_dist_factor * min_dist, .1);
  while (i != end(image_pair->matches)) {
    if (i->distance <= allowed_dist)
      ++i;
    else
      i = image_pair->matches.erase(i);
  }

#ifdef DEBUG
  printf("FeatureMatcher: Filtered out %lu bad pairs, kept %lu pairs (%s vs %s).\n",
         matches_before - image_pair->matches.size(),
         image_pair->matches.size(), image_pair->image1->file_name().c_str(), image_pair->image2->file_name().c_str());
#endif

}