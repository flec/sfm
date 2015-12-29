// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iomanip>
#include "plyutil.h"


void PlyUtil::write(const string &fileName, const vector<shared_ptr<ObjectPoint>> &object_points) {
  ofstream file(fileName.c_str());

  if (!file) {
    cerr << "Error opening output file: " << fileName << "!" << endl;
    exit(1);
  }

  file << "ply" << endl;
  file << "format ascii 1.0" << endl;
  file << "element vertex " << object_points.size() << endl;
  file << "property float x" << endl;
  file << "property float y" << endl;
  file << "property float z" << endl;
  file << "property uchar red" << endl;
  file << "property uchar green" << endl;
  file << "property uchar blue" << endl;
  //file << "element face " << triangleNum << endl;
  //file << "property list uchar int vertex_index" << endl;
  file << "end_header" << endl;

  file << fixed << setprecision(8);

  for (auto object_point:object_points) {
    Point3f *coords = object_point->gl_coordinates();
    Point3f color = object_point->color();
    file << coords->x << " " << coords->y << " " << coords->z <<
    " " << (int) (color.x * 255) << " " << (int) (color.y * 255) << " " << (int) (color.z * 255) << endl;
  }

}
