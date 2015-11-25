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
  Point3f coordinates_;
  Point3f color_;
  // vector of references (using vector instead of map to avoid key conflicts and two vectors instead of pair because of forward declaration)
  vector<int> refKeypoints;
  vector<shared_ptr<Image>> refImages;
public:
  ObjectPoint(float x, float y, float z, float r = 1.0f, float g = 0.0f, float b = 0.0f);

  Point3f *coordinates() { return &coordinates_; }

  void addReference(int keypointIndex, shared_ptr<Image> image);

  const Point3f &color() const { return color_; }
};

#endif //SFM_OBJECTPOINT_H