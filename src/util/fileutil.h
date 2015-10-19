//
// Created by joschi on 19.10.15.
//

#ifndef SFM_FILEUTIL_H
#define SFM_FILEUTIL_H

#include <string>

using namespace std;

#ifndef _WIN32
const char FILE_SEPARATOR = '/';
#else
const char FILE_SEPARATOR= '\\';
#endif

class FileUtil {
public:
  static string getPathName(const string &s);
};


#endif //SFM_FILEUTIL_H
