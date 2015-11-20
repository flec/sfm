//
// Created by marco on 20.11.15.
//

#include "testcube.h"

void TestCube::getMatches(vector <Point2f> *points1, vector <Point2f> *points2) {
  points1->push_back(Point2f(209, 323));
  points1->push_back(Point2f(440, 272));
  points1->push_back(Point2f(760, 298));
  points1->push_back(Point2f(594, 368));
  points1->push_back(Point2f(238, 705));
  points1->push_back(Point2f(583, 812));
  points1->push_back(Point2f(736, 644));
  points1->push_back(Point2f(588, 604));

  points2->push_back(Point2f(209, 318));
  points2->push_back(Point2f(460, 272));
  points2->push_back(Point2f(770, 302));
  points2->push_back(Point2f(564, 370));
  points2->push_back(Point2f(238, 694));
  points2->push_back(Point2f(556, 816));
  points2->push_back(Point2f(745, 653));
  points2->push_back(Point2f(560, 607));
}