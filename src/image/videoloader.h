// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_VIDEOLOADER_H
#define SFM_VIDEOLOADER_H

#include "image.h"
#include <string>
#include <memory>

using namespace std;

/**
 * Class for loading video frames
 */
class VideoLoader {
public:
  /**
   * Loads every nth frame from video
   *
   * file_name  Videos file name
   * n          The nth frame that should be loaded
   * returns    A vector containing all loaded Images
   */
  static vector<shared_ptr<Image>> loadVideoFrames(const string &file_name, const int n = 20);
};

#endif //SFM_VIDEOLOADER_H
