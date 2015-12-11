// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_OBJECTPOINT_H
#define SFM_OBJECTPOINT_H


#include <opencv2/core/types.hpp>
#include <utility>
#include <memory>
#include "image/pair/keypointimagepair.h"

// forward declaration
class Image;

using namespace std;
using namespace cv;

// Represents a point of the 3D object
class ObjectPoint {
private:
  Point3f coordinates_;

  // rotated by 180? around the X axis
  // OpenCV: x goes top-down, y left to right
  // OpenGL: x(-axis) goes bottom-up, y left to right
  Point3f gl_coordinates_;

  Point3f color_;

  static Mat_<float> rotate_x_axis_180;

  vector<KeyPointImagePair> references_;

  void updateGlCoordinates();

public:

  ObjectPoint(float x, float y, float z);

  void updateCoordinates(float x, float y, float z);

  Point3f *coordinates() { return &coordinates_; }

  Point3f *gl_coordinates() { return &gl_coordinates_; }

  unsigned long getNumReferences() { return references_.size(); }

  vector<KeyPointImagePair> *references() { return &references_; }

  void addReference(int keypointIndex, shared_ptr<Image> image);

  void removeReferencesToImage(shared_ptr<Image> image);

  const Point3f &color() const { return color_; }

  void recalculateColor();
};

#endif //SFM_OBJECTPOINT_H

