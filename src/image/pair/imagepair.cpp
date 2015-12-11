// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "imagepair.h"

void ImagePair::getMatches(vector<Point2f> &points1, vector<Point2f> &points2) {
  vector<KeyPoint> *keypoints1 = this->image1->keypoints();
  vector<KeyPoint> *keypoints2 = this->image2->keypoints();

  points1.clear();
  points2.clear();

  for (auto match:this->matches) {
    points1.push_back(keypoints1->at(match.queryIdx).pt);
    points2.push_back(keypoints2->at(match.trainIdx).pt);
  }
}

void ImagePair::clearMatrices() {
  rotation.release();
  translation.release();
  essential.release();

  projection_img1.release();
  projection_img2.release();

  triangulation_points1.clear();
  triangulation_points2.clear();

  pnp_object_points.clear();
  pnp_image_points.clear();
}
