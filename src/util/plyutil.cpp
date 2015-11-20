//
// Created by marco on 19.11.15.
//

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
  file << "element vertex " << points3Dh.rows << endl;
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