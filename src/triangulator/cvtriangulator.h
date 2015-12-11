// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_BASETRIANGULATOR_H
#define SFM_BASETRIANGULATOR_H

#include "triangulator.h"

class CVTriangulator : public Triangulator {
public:
  void findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters, map<int, Point3f> &map_points3D);
};
#endif //SFM_BASETRIANGULATOR_H
