//
// Created by marco on 18.11.15.
//

#ifndef SFM_OBJECTPOINT_H
#define SFM_OBJECTPOINT_H


#include <opencv2/core/types.hpp>

using namespace std;
using namespace cv;

// Represents a point of the 3D object
class ObjectPoint {
private:

public:
  Point3f coordinates;
};

#endif //SFM_OBJECTPOINT_H