//
// Created by joschi on 30.10.15.
//

#include "imagepair.h"

void ImagePair::getMatches(vector<Point2f> &points1, vector<Point2f> &points2) {
  if (matches1.size() != matches.size()) {

    vector<KeyPoint> *keypoints1 = this->image1->get_keypoints();
    vector<KeyPoint> *keypoints2 = this->image2->get_keypoints();

    matches1.clear();
    matches2.clear();

    for (auto match:this->matches) {
      matches1.push_back(keypoints1->at(match.queryIdx).pt);
      matches2.push_back(keypoints2->at(match.trainIdx).pt);
    }
  }

  points1 = matches1;
  points2 = matches2;
}

void ImagePair::clearMatrices() {
  rotation.release();
  translation.release();
  essential.release();

  projection_img1.release();
  projection_img2.release();

  rotation_rect_img1.release();
  rotation_rect_img2.release();

  triangulation_points1.clear();
  triangulation_points2.clear();

  pnp_object_points.clear();
  pnp_image_points.clear();

  matches1.clear();
  matches2.clear();
}
