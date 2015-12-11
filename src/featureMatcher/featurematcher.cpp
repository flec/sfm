// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "featurematcher.h"

void FeatureMatcher::filterMatches(shared_ptr<ImagePair> &image_pair, double min_dist_factor) {
#ifdef DEBUG
  signed int matches_before = image_pair->matches.size();
#endif
  double min_dist = DBL_MAX;
  double max_dist = 0;

  // calc min and max distance between keypoints_
  for (auto match : image_pair->matches) {
    if (match.distance < min_dist) min_dist = match.distance;
    if (match.distance > max_dist) max_dist = match.distance;
  }

  // erase bad pairs
  auto i = begin(image_pair->matches);
  while (i != end(image_pair->matches)) {
    if (i->distance < min_dist_factor * min_dist) {

      ++i;
    }
    else {
      i = image_pair->matches.erase(i);
    }
  }

#ifdef DEBUG
  printf("FeatureMatcher: Filtered out %lu bad pairs, kept %lu pairs.\n", matches_before - image_pair->matches.size(),
         image_pair->matches.size());
#endif

}