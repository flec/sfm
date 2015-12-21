// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_OPTICALFLOWFEATUREMATCHER_H
#define SFM_OPTICALFLOWFEATUREMATCHER_H

#include "featurematcher.h"

/**
 * Implementation of a feature matcher that uses optical flow for matching
 */
class OpticalFlowFeatureMatcher : public FeatureMatcher {
private:
  /**
   * Maximum error for points
   */
  static const float MAX_OPTICAL_FLOW_ERROR;

  /**
   * Maximum distance a point can have to a key point to be matched to it
   */
  static const float MAX_DISTANCE_TO_KEYPOINT;

  /**
   * Maximum distance ratio that the two closest key points to the point can have that has been detected using optical flow.
   */
  static const float MAX_NEIGHBOR_DISTANCE_RATIO;

  /**
   * Extracts the key points from the image and converts them to Point2f
   *
   * image    image where the key points should be extracted from
   * points   output: key points as Point2f
   */
  void keyPointsAsPoints(const shared_ptr<Image> &image, vector<Point2f> &points);

  /**
   * Filters points using the status and error vector
   *
   * points               vector of points to filter
   * status               vector of status from optical flow
   * error                vector of errors from optical flow
   * good_points          output: good points
   * good_point_indices   output: indices of good points based on original points
   */
  void filterPoints(const vector<Point2f> &points, const vector<uchar> &status, const vector<float> &error,
                    Mat &good_points, vector<int> &good_points_indices);

  /**
   * Finds closest matching key points in the image for the given points
   *
   * image            image that contains the key points that should be matched
   * points           points found through optical flow that should be matched with key points in the image
   * points_indices   indices of points that correspond to the key points in the first image
   * matches          output: found matches
   */
  void findMatches(const shared_ptr<Image> &image, const Mat &points, const vector<int> &points_indices,
                   vector<DMatch> &matches);

public:
  /**
   * @see FeatureMatcher
   */
  shared_ptr<ImagePair> matchFeatures(shared_ptr<Image> &image1, shared_ptr<Image> &image2);
};

#endif //SFM_OPTICALFLOWFEATUREMATCHER_H
