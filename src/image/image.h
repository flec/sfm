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
    Mat mat_color;
    Mat mat_grey;
    string file_name;
    string file_path;
public:
    Image(string const& file_path);

    Image(string const& file_path, bool const only_grey);

    ~Image();

    Mat get_mat_color() const { return mat_color.data ? mat_color : mat_grey; }

    Mat get_mat_grey() const { return mat_grey; }

    string get_file_name() const { return file_name; }

    string get_file_path() const { return file_path; }
};


#endif //SFM_IMAGE_H
