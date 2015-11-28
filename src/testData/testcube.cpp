//
// Created by marco on 20.11.15.
//

#include "testcube.h"

void TestCube::setKeypointsPair1(vector<KeyPoint> &keyPoints1, vector<KeyPoint> &keyPoints2) {
  keyPoints1.push_back(KeyPoint(Point2f(209, 323), 1));
  keyPoints1.push_back(KeyPoint(Point2f(440, 272), 1));
  keyPoints1.push_back(KeyPoint(Point2f(760, 298), 1));
  keyPoints1.push_back(KeyPoint(Point2f(594, 368), 1));
  keyPoints1.push_back(KeyPoint(Point2f(238, 705), 1));
  keyPoints1.push_back(KeyPoint(Point2f(583, 812), 1));
  keyPoints1.push_back(KeyPoint(Point2f(736, 644), 1));
  keyPoints1.push_back(KeyPoint(Point2f(588, 604), 1));

  keyPoints2.push_back(KeyPoint(Point2f(209, 318), 1));
  keyPoints2.push_back(KeyPoint(Point2f(460, 272), 1));
  keyPoints2.push_back(KeyPoint(Point2f(770, 302), 1));
  keyPoints2.push_back(KeyPoint(Point2f(564, 370), 1));
  keyPoints2.push_back(KeyPoint(Point2f(238, 694), 1));
  keyPoints2.push_back(KeyPoint(Point2f(556, 816), 1));
  keyPoints2.push_back(KeyPoint(Point2f(745, 653), 1));
  keyPoints2.push_back(KeyPoint(Point2f(560, 607), 1));
}

void TestCube::setKeypointsPair2(vector<KeyPoint> &keyPoints1, vector<KeyPoint> &keyPoints2) {
  keyPoints1.push_back(KeyPoint(Point2f(209, 318), 1));
  keyPoints1.push_back(KeyPoint(Point2f(460, 272), 1));
  keyPoints1.push_back(KeyPoint(Point2f(770, 302), 1));
  keyPoints1.push_back(KeyPoint(Point2f(564, 370), 1));
  keyPoints1.push_back(KeyPoint(Point2f(238, 694), 1));
  keyPoints1.push_back(KeyPoint(Point2f(556, 816), 1));
  keyPoints1.push_back(KeyPoint(Point2f(745, 653), 1));
  keyPoints1.push_back(KeyPoint(Point2f(560, 607), 1));
  keyPoints1.push_back(KeyPoint(Point2f(757, 486), 1));

  keyPoints2.push_back(KeyPoint(Point2f(212, 314), 1));
  keyPoints2.push_back(KeyPoint(Point2f(480, 271), 1));
  keyPoints2.push_back(KeyPoint(Point2f(778, 306), 1));
  keyPoints2.push_back(KeyPoint(Point2f(532, 370), 1));
  keyPoints2.push_back(KeyPoint(Point2f(240, 683), 1));
  keyPoints2.push_back(KeyPoint(Point2f(529, 818), 1));
  keyPoints2.push_back(KeyPoint(Point2f(752, 663), 1));
  keyPoints2.push_back(KeyPoint(Point2f(530, 608), 1));
  keyPoints2.push_back(KeyPoint(Point2f(765, 493), 1));
}

void TestCube::setMatches(int num, vector<DMatch> &matches) {
  for (int i = 0; i < num; i++) {
    matches.push_back(DMatch(i, i, 0));
  }
}

shared_ptr<ImagePair> TestCube::getPair1() {
  shared_ptr<ImagePair> image_pair(new ImagePair());
  image_pair->image1 = shared_ptr<Image>(new Image());
  image_pair->image2 = shared_ptr<Image>(new Image());
  TestCube::setKeypointsPair1(image_pair->image1->keypoints_, image_pair->image2->keypoints_);
  TestCube::setMatches(8, image_pair->matches);
  return image_pair;
}

shared_ptr<ImagePair> TestCube::getPair2() {
  shared_ptr<ImagePair> image_pair(new ImagePair());
  image_pair->image1 = shared_ptr<Image>(new Image());
  image_pair->image2 = shared_ptr<Image>(new Image());
  TestCube::setKeypointsPair2(image_pair->image1->keypoints_, image_pair->image2->keypoints_);
  TestCube::setMatches(9, image_pair->matches);
  return image_pair;
}

Mat_<double> TestCube::getIntrinsicMatrix() {
  return (Mat_<double>(3, 4) <<
          1207.1067811865476, 0.0, 500.0,
      0.0, 1207.1067811865476, 500.0,
      0.0, 0.0, 1.0
  );
}
