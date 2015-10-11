#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

vector<Mat> loadImageFromDir(string dirName);