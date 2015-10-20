//
// Created by joschi on 19.10.15.
//

#include "fileutil.h"

string FileUtil::getPathName(const string &s) {


  size_t i = s.rfind(FILE_SEPARATOR, s.length());
  if (i != string::npos) {
    return (s.substr(0, i));
  }

  return ("");
}


string FileUtil::getFileName(const string &s) {


  size_t i = s.rfind(FILE_SEPARATOR, s.length());
  if (i != string::npos) {
    return (s.substr(i+1));
  }

  return ("");
}
