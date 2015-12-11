// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "testcube.h"

void TestCube::setKeypointsImg1(vector<KeyPoint> &keyPoints) {
  keyPoints.push_back(KeyPoint(Point2f(209, 323), 1));
  keyPoints.push_back(KeyPoint(Point2f(440, 272), 1));
  keyPoints.push_back(KeyPoint(Point2f(760, 298), 1));
  keyPoints.push_back(KeyPoint(Point2f(594, 368), 1));
  keyPoints.push_back(KeyPoint(Point2f(238, 705), 1));
  keyPoints.push_back(KeyPoint(Point2f(583, 812), 1));
  keyPoints.push_back(KeyPoint(Point2f(736, 644), 1));
  keyPoints.push_back(KeyPoint(Point2f(588, 604), 1));
}

void TestCube::setKeypointsImg2(vector<KeyPoint> &keyPoints) {
  keyPoints.push_back(KeyPoint(Point2f(209, 318), 1));
  keyPoints.push_back(KeyPoint(Point2f(460, 272), 1));
  keyPoints.push_back(KeyPoint(Point2f(770, 302), 1));
  keyPoints.push_back(KeyPoint(Point2f(564, 370), 1));
  keyPoints.push_back(KeyPoint(Point2f(238, 694), 1));
  keyPoints.push_back(KeyPoint(Point2f(556, 816), 1));
  keyPoints.push_back(KeyPoint(Point2f(745, 653), 1));
  keyPoints.push_back(KeyPoint(Point2f(560, 607), 1));
  keyPoints.push_back(KeyPoint(Point2f(757, 486), 1));
}

void TestCube::setKeypointsImg3(vector<KeyPoint> &keyPoints) {
  keyPoints.push_back(KeyPoint(Point2f(212, 314), 1));
  keyPoints.push_back(KeyPoint(Point2f(480, 271), 1));
  keyPoints.push_back(KeyPoint(Point2f(778, 306), 1));
  keyPoints.push_back(KeyPoint(Point2f(532, 370), 1));
  keyPoints.push_back(KeyPoint(Point2f(240, 683), 1));
  keyPoints.push_back(KeyPoint(Point2f(529, 818), 1));
  keyPoints.push_back(KeyPoint(Point2f(752, 663), 1));
  keyPoints.push_back(KeyPoint(Point2f(530, 608), 1));
  keyPoints.push_back(KeyPoint(Point2f(765, 493), 1));
}

void TestCube::setMatches(int num, vector<DMatch> &matches) {
  for (int i = 0; i < num; i++) {
    matches.push_back(DMatch(i, i, 0));
  }
}

void TestCube::setPairs(vector<shared_ptr<ImagePair>> &pairs) {
  shared_ptr<Image> image1(new Image());
  shared_ptr<Image> image2(new Image());
  shared_ptr<Image> image3(new Image());
  shared_ptr<ImagePair> pair1(new ImagePair());
  shared_ptr<ImagePair> pair2(new ImagePair());

  pair1->image1 = image1;
  pair1->image2 = image2;
  pair2->image1 = image2;
  pair2->image2 = image3;

  TestCube::setKeypointsImg1(image1->keypoints_);
  TestCube::setKeypointsImg2(image2->keypoints_);
  TestCube::setKeypointsImg3(image3->keypoints_);

  TestCube::setMatches(8, pair1->matches);
  TestCube::setMatches(9, pair2->matches);

  pairs.push_back(pair1);
  pairs.push_back(pair2);
}

Mat_<double> TestCube::getIntrinsicMatrix() {
  return (Mat_<double>(3, 4) <<
          1207.1067811865476, 0.0, 500.0,
      0.0, 1207.1067811865476, 500.0,
      0.0, 0.0, 1.0
  );
}
