// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <set>
#include <opencv2/video/tracking.hpp>
#include <opencv2/features2d.hpp>
#include "opticalflowfeaturematcher.h"

shared_ptr<ImagePair> OpticalFlowFeatureMatcher::matchFeatures(shared_ptr<Image> &image1, shared_ptr<Image> &image2) {
  shared_ptr<ImagePair> image_pair(new ImagePair());
  image_pair->image1 = image1;
  image_pair->image2 = image2;

  // setup key points
  vector<Point2f> points1;
  vector<Point2f> points2;
  keyPointsAsPoints(image1, points1);

  // calculate optical flow
  vector<uchar> status;
  vector<float> error;
  calcOpticalFlowPyrLK(*image1->mat_grey(), *image2->mat_grey(), points1, points2, status, error);

  // get good points
  vector<int> good_point_indices;
  Mat good_points;
  filterPoints(points2, status, error, good_points, good_point_indices);

  // get matches in image2
  findMatches(image2, good_points, good_point_indices, image_pair->matches);

  return image_pair;
}

void OpticalFlowFeatureMatcher::keyPointsAsPoints(const shared_ptr<Image> &image, vector<Point2f> &points) {
  unsigned long num_keypoints = image->keypoints()->size();
  points.reserve(num_keypoints);
  for (unsigned int i = 0; i < num_keypoints; i++) {
    points.push_back(image->keypoints()->at(i).pt);
  }
}

void OpticalFlowFeatureMatcher::filterPoints(const vector<Point2f> &points, const vector<uchar> &status,
                                             const vector<float> &error,
                                             Mat &good_points, vector<int> &good_points_indices) {
  vector<Point2f> vec_good_points;
  for (unsigned int i = 0; i < points.size(); i++) {
    if (status[i] && error[i] < 12.0) {
      good_points_indices.push_back(i);
      vec_good_points.push_back(points.at(i));
    }
  }

  good_points = Mat(vec_good_points).reshape(1, vec_good_points.size());
}

void OpticalFlowFeatureMatcher::findMatches(const shared_ptr<Image> &image, const Mat &points,
                                            const vector<int> &points_indices, vector<DMatch> &matches) {
  // convert features from image into Mat format
  vector<Point2f> vec_features;
  keyPointsAsPoints(image, vec_features);
  Mat features = Mat(vec_features).reshape(1, vec_features.size());

  // find key points in specified radius
  BFMatcher matcher(CV_L2);
  vector<vector<DMatch>> nearest_neighbors;
  matcher.radiusMatch(points, features, nearest_neighbors, 2.0f);

  // filter neighbors
  set<int> found;
  for (auto nn_matches : nearest_neighbors) {
    // use match if there is only one or the first and the second are not to close
    if (nn_matches.size() == 1 ||
               (nn_matches.size() > 1 && (nn_matches.at(0).distance / nn_matches.at(1).distance) < 0.7)) {
      DMatch match = nn_matches.at(0);
      // add match if not already matched to another point
      if (found.find(match.trainIdx) == found.end()) {
        found.insert(match.trainIdx); // mark key point as matched
        match.queryIdx = points_indices.at(match.queryIdx); // set query index to key point index from first image
        matches.push_back(match);
      }
    }

  }
}
