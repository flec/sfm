//
// Created by joschi on 19.10.15.
//

#include <dirent.h>
#include <stdexcept>
#include "imageloader.h"

vector<Image> ImageLoader::loadImagesFromDir(string const &dirName) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(dirName.c_str())) != NULL) {
    vector<Image> images;
    while ((ent = readdir(dir)) != NULL) {
      printf("Loading image %s\n", ent->d_name);
      Image *image = new Image(ent->d_name);
      images.push_back(*image);
    }
    closedir(dir);
  } else {
    string msg = "ImageLoader::loadImagesFromDir: cannot open directory " + dirName;
    throw std::runtime_error(msg);
  }
}
