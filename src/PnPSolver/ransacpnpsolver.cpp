//
// Created by marco on 22.11.15.
//

#include "ransacpnpsolver.h"

void RANSACPnPSolver::solve(shared_ptr <ImagePair> &image_pair, Mat &intristic_camera_paramaters) {
  vector<Point3f> objectPoints;
  vector<Point2f> imagePoints;

  vector<KeyPoint> *keypoints2 = image_pair->image2->get_keypoints();

  for (auto match:image_pair->matches) {
    objectPoints.push_back(image_pair->image1->getObjectPoint(match.queryIdx)->getCoordinates());
    imagePoints.push_back(keypoints2->at(match.trainIdx).pt);
  }

  solvePnPRansac(objectPoints, imagePoints, intristic_camera_paramaters, noArray(), image_pair->rotation, image_pair->translation);
}