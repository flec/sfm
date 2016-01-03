// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <opencv2/videoio.hpp>
#include "videoloader.h"
#include "videoloadexception.h"

using namespace cv;

vector<shared_ptr<Image>> VideoLoader::loadVideoFrames(const string &file_name, const int n) {
  vector<shared_ptr<Image>> images;
  VideoCapture capture(file_name);
  if (!capture.isOpened()) {
    throw VideoLoadException("VideoLoader::loadVideoFrames cannot load video " + file_name);
  }

  Mat frame;
  unsigned int i = 0;
  while (capture.read(frame)) {
    if (i % n == 0) {
      char index[10];
      sprintf(index, "(%d)", i);
      images.push_back(shared_ptr<Image>(new Image(file_name + index, frame)));
    }
    i++;
  }

  capture.release();
  return images;
}