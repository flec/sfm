//
// Created by joschi on 19.10.15.
//

#ifndef SFM_IMAGE_H
#define SFM_IMAGE_H

#include <opencv2/core/mat.hpp>

using namespace cv;
using namespace std;

struct Image {
private:
  vector<KeyPoint> keypoints;

  Mat mat_color;
  Mat mat_grey;

  string file_name;
  string file_path;

  Image() { };

public:
  Mat descriptors;
  Image(string const &file_path, bool const load_color = true);

  ~Image();

  Mat* get_mat_color() { return (mat_color.data != NULL) ? &mat_color : &mat_grey; }

  Mat* get_mat_grey() { return &mat_grey; }

  string get_file_name() const { return file_name; }

  string get_file_path() const { return file_path; }

  vector<KeyPoint> *get_keypoints() { return &keypoints; }

  Mat* get_descriptors() { return &descriptors; }
};


#endif //SFM_IMAGE_H
