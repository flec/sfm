// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iomanip>
#include "plyutil.h"

void PlyUtil::write(const string &fileName, const Mat &points3Dh) {

  ofstream file(fileName.c_str());

  if (!file) {
    cerr << "Error opening output file: " << fileName << "!" << endl;
    exit(1);
  }

  file << "ply" << endl;
  file << "format ascii 1.0" << endl;
  file << "element vertex " << points3Dh.cols << endl;
  file << "property float x" << endl;
  file << "property float y" << endl;
  file << "property float z" << endl;
  //file << "element face " << triangleNum << endl;
  //file << "property list uchar int vertex_index" << endl;
  file << "end_header" << endl;

  file << fixed << setprecision(8);

  for (int c = 0; c < points3Dh.cols; c++) {
    for (int r = 0; r < 3; r++) {
      file << points3Dh.at<float>(r, c) << " ";
    }
    file << endl;
  }

}

void PlyUtil::write(const string &fileName, const vector<shared_ptr<ObjectPoint>> &objectPoints) {
  ofstream file(fileName.c_str());

  if (!file) {
    cerr << "Error opening output file: " << fileName << "!" << endl;
    exit(1);
  }

  file << "ply" << endl;
  file << "format ascii 1.0" << endl;
  file << "element vertex " << objectPoints.size() << endl;
  file << "property float x" << endl;
  file << "property float y" << endl;
  file << "property float z" << endl;
  //file << "element face " << triangleNum << endl;
  //file << "property list uchar int vertex_index" << endl;
  file << "end_header" << endl;

  file << fixed << setprecision(8);

  for (auto objectPoint:objectPoints) {
    Point3f *coords = objectPoint->coordinates();
    file << coords->x << " " << coords->y << " " << coords->z << endl;
  }

}
