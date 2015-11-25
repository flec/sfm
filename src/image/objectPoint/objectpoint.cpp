//
// Created by marco on 18.11.15.
//

#include "objectpoint.h"

using namespace std;
using namespace cv;

void ObjectPoint::addReference(int keypointIndex, shared_ptr<Image> image) {
  this->refKeypoints.push_back(keypointIndex);
  this->refImages.push_back(image);
}

ObjectPoint::ObjectPoint(float x, float y, float z, float r, float g, float b) :
    coordinates_(x, y, z), color_(r, g, b) {

}
