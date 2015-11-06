//
// Created by joschi on 04.11.15.
//

#include "featurematcher.h"

void FeatureMatcher::filterMatches(shared_ptr<FeatureMatches> &matches, double min_dist_factor) {
  signed int matches_before = matches->matches.size();
  double min_dist = DBL_MAX;
  double max_dist = 0;

  // calc min and max distance between keypoints
  for (auto match : matches->matches) {
    if (match.distance < min_dist) min_dist = match.distance;
    if (match.distance > max_dist) max_dist = match.distance;
  }

  // erase bad matches
  auto i = begin(matches->matches);
  while (i != end(matches->matches)) {
    if (i->distance > min_dist_factor * min_dist)
      i = matches->matches.erase(i);
    else
      ++i;
  }

#ifdef DEBUG
  printf("Filtered out %d bad matches.\n", matches_before-matches->matches.size());
#endif

}