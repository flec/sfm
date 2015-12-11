// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

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
  static string getFileName(const string &s);
};


#endif //SFM_FILEUTIL_H
