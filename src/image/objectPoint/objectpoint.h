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

/**
 * Representation of a point of the 3D object
 */
class ObjectPoint {
private:
  Point3f coordinates_;

  /**
   * coordinates rotated by 180° around the X axis
   * OpenCV: x goes top-down, y left to right
   * OpenGL: x(-axis) goes bottom-up, y left to right
   */
  Point3f gl_coordinates_;

  /**
   * Points color
   */
  Point3f color_;

  /**
   * Matrix to calculate the gl coordinates
   */
  static Mat_<float> rotate_x_axis_180;

  /**
   * Image key points that see this 3D point
   */
  vector<KeyPointImagePair> references_;

  /**
   * Recalculates the gl coordinates based on the coordinates set in the object
   */
  void updateGlCoordinates();

public:

  /**
   * Constructor to set the points coordinates
   * x  values of x-coordinate
   * y  values of y-coordinate
   * z  values of z-coordinate
   */
  ObjectPoint(float x, float y, float z);

  /**
   * Updates the points ccoordinates
   * x  values of x-coordinate
   * y  values of y-coordinate
   * z  values of z-coordinate
   */
  void updateCoordinates(float x, float y, float z);

  /**
   * Getter for coordinates
   */
  Point3f *coordinates() { return &coordinates_; }

  /**
   * Getter for gl coordinates
   */
  Point3f *gl_coordinates() { return &gl_coordinates_; }

  /**
   * Returns how many key points (images) reference this point
   */
  unsigned long getNumReferences() { return references_.size(); }

  /**
   * Getter for key points (images) that reference this point
   */
  vector<KeyPointImagePair> *references() { return &references_; }

  /**
   * Adds a reference to this point. This means that this point can be seen from that key point (image)
   * key_point_index  index ot the key point that sees that 3D point
   * image            image where the key point belongs to
   */
  void addReference(int key_point_index, shared_ptr<Image> image);

  /**
   * Removes a reference to an image (key point) for this 3D point
   * image  image reference that should be removed
   */
  void removeReferencesToImage(shared_ptr<Image> image);

  /**
   * Getter for color of this point
   */
  const Point3f &color() const { return color_; }

  /**
   * Recalculates color based on the referenced key points
   */
  void recalculateColor();
};

#endif //SFM_OBJECTPOINT_H

