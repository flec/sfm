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
  vector<string> files = read_directory(dirName);
  if (errno == 0) {
    vector<shared_ptr<Image>> images;
    for(auto file_name : files){
      try {
        shared_ptr<Image>image (new Image(dirName + file_name));
        images.push_back(image);
      } catch (const ImageLoadException& e) {
#ifdef DEBUG
        printf("Caugth exception %s\n", e.what());
#endif
      }
    }
    return images;
  } else {
    throw ImageLoadException("ImageLoader::loadImagesFromDir(): cannot open directory  " + dirName);
  }
}

// read_directory()
//   Return an ASCII-sorted vector of filename entries in a given directory.
//   If no path is specified, the current working directory is used.
//
//   Always check the value of the global 'errno' variable after using this
//   function to see if anything went wrong. (It will be zero if all is well.)
//
vector <string> ImageLoader::read_directory( const string& path)
{
  vector <string> result;
  dirent* de;
  DIR* dp;
  errno = 0;
  dp = opendir( path.empty() ? "." : path.c_str() );
  if (dp)
  {
    while (true)
    {
      errno = 0;
      de = readdir( dp );
      if (de == NULL) break;
      result.push_back( string( de->d_name ) );
    }
    closedir( dp );
    sort( result.begin(), result.end() );
  }
  return result;
}