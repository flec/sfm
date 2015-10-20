//
// Created by joschi on 19.10.15.
//

#include <dirent.h>
#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include "imageloader.h"
#include "imageloadexception.h"

using namespace std;

vector<shared_ptr<Image>> ImageLoader::loadImagesFromDir(string const &dirName) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(dirName.c_str())) != NULL) {
    vector<shared_ptr<Image>> images;
    while ((ent = readdir(dir)) != NULL) {
      try {
        shared_ptr<Image>image (new Image(dirName + ent->d_name));
        images.push_back(image);
      } catch (const ImageLoadException& e) {
#ifdef DEBUG
        printf("Caugth exception %s\n", e.what());
#endif
      }
    }
    closedir(dir);
    return images;
  } else {
    throw ImageLoadException("ImageLoader::loadImagesFromDir(): cannot open directory  " + dirName);
  }
}
