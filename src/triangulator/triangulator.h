// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_TRIANGULATOR_H
#define SFM_TRIANGULATOR_H

#include <memory>
#include "image/pair/imagepair.h"

/**
 * Interface for a triangulator that triangulates 2D points to obtain 3D points
 */
class Triangulator {
public:
  /**
   * Triangulates the specified points for triangulation in both images of the pair to obtain 3D points.
   * If outliners are removed the map returned does only contain indices with inliners.
   *
   * image_pair                   pair of images that should be triangulated
   * intrinsic_camera_parameters  intrinsic camera parameters
   * map_points3D                 output: map with triangulated inliner 3D points where the key corresponds to the indices in vector of points for triangulation
   */
  virtual void findPoints3D(shared_ptr <ImagePair> &image_pair, Mat &intrinsic_camera_parameters, map<int, Point3f> &map_points3D) = 0;

};

#endif // SFM_TRIANGULATOR_H