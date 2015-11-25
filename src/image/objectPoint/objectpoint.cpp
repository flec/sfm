//
// Created by marco on 18.11.15.
//

#include "objectpoint.h"

using namespace std;
using namespace cv;

ObjectPoint::ObjectPoint(float x, float y, float z) {
  this->coordinates_ = Point3f(x, y, z);
}

void ObjectPoint::addReference(int keypointIndex, shared_ptr<Image> image) {
  this->refKeypoints.push_back(keypointIndex);
  this->refImages.push_back(image);
}