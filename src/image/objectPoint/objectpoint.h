//
// Created by marco on 18.11.15.
//

#ifndef SFM_OBJECTPOINT_H
#define SFM_OBJECTPOINT_H

#include <memory>
#include <vector>
#include <map>
#include <image/image.h>
#include <opencv2/core/mat.hpp>

using namespace std;
using namespace cv;

// Represents a point of the 3D object
class ObjectPoint {
private:

public:
  Point3f coordinates;
};

#endif //SFM_OBJECTPOINT_H