// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

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
