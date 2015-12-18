// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_FILEUTIL_H
#define SFM_FILEUTIL_H

#include <string>

using namespace std;

#ifdef _WIN32
const char FILE_SEPARATOR= '\\';
#else
const char FILE_SEPARATOR = '/';
#endif

/**
 * Utility functions for file operations
 */
class FileUtil {
public:
  /**
   * Returns the path without file name from entire file path
   * s        entire file path
   * returns  path without file name
   */
  static string getPathName(const string &s);

  /**
   * Returns file name from entire path
   * s        entire path
   * returns  file name
   */
  static string getFileName(const string &s);
};


#endif //SFM_FILEUTIL_H
