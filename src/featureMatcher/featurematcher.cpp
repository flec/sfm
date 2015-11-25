//
// Created by joschi on 04.11.15.
//

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

  // erase bad pair
  auto i = begin(image_pair->matches);
  while (i != end(image_pair->matches)) {
    if (i->distance > min_dist_factor * min_dist)
      i = image_pair->matches.erase(i);
    else
      ++i;
  }

#ifdef DEBUG
  printf("Filtered out %lu bad pairs.\n", matches_before - image_pair->matches.size());
#endif

}