//
// Created by marco on 18.11.15.
//

#ifndef SFM_OBJECTPOINT_H
#define SFM_OBJECTPOINT_H


#include <opencv2/core/types.hpp>
#include <utility>
#include <memory>

// forward declaration
class Image;

using namespace std;
using namespace cv;

// Represents a point of the 3D object
class ObjectPoint {
private:
  Point3f coordinates;
  // vector of references (using vector instead of map to avoid key conflicts and two vectors instead of pair because of forward declaration)
  vector<int> refKeypoints;
  vector<shared_ptr<Image>> refImages;
public:
  ObjectPoint(float x, float y, float z);
  Point3f* getCoordinates() { return &this->coordinates; }
  void addReference(int keypointIndex, shared_ptr<Image> image);
};

#endif //SFM_OBJECTPOINT_H