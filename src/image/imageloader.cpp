// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <dirent.h>
#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include "imageloader.h"
#include "imageloadexception.h"

using namespace std;

vector<shared_ptr<Image>> ImageLoader::loadImagesFromDir(string const &dir_name) {
  vector<string> files = read_directory(dir_name);
  if (errno == 0) {
    vector<shared_ptr<Image>> images;

    // Load images in a parallel fashion
#pragma omp parallel
    {
      vector<shared_ptr<Image>> images_private;
#pragma omp for nowait schedule(static)
      for (int i = 0; i < files.size(); i++) {
        try {
          shared_ptr<Image> image(new Image(dir_name + files.at(i)));
          images_private.push_back(image);
        } catch (const ImageLoadException &e) {
#ifdef DEBUG
          printf("Caugth exception %s\n", e.what());
#endif
        }
      }
#pragma omp for schedule(static) ordered
      for (int i = 0; i < omp_get_num_threads(); i++) {
#pragma omp ordered
        images.insert(images.end(), images_private.begin(), images_private.end());
      }
    }
    return images;
  } else {
    throw ImageLoadException("ImageLoader::loadImagesFromDir(): cannot open directory  " + dir_name);
  }
}

vector<string> ImageLoader::read_directory(const string &path) {
  vector<string> result;
  dirent *de;
  DIR *dp;
  errno = 0;
  dp = opendir(path.empty() ? "." : path.c_str());
  if (dp) {
    while (true) {
      errno = 0;
      de = readdir(dp);
      if (de == NULL) break;
      result.push_back(string(de->d_name));
    }
    closedir(dp);
    sort(result.begin(), result.end());
  }
  return result;
}