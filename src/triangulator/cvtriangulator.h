//
// Created by marco on 18.11.15.
//

#ifndef SFM_BASETRIANGULATOR_H
#define SFM_BASETRIANGULATOR_H

#include "triangulator.h"

class CVTriangulator : public Triangulator {
public:
  void findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters, map<int, Point3f> &map_points3D);
};
#endif //SFM_BASETRIANGULATOR_H
