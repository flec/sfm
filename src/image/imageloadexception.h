// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_IMAGELOADEXCEPTION_H
#define SFM_IMAGELOADEXCEPTION_H

class ImageLoadException : public std::runtime_error {
public:
  ImageLoadException() : runtime_error("Image could not be loaded.") { }

  ~ImageLoadException() throw() { }

  ImageLoadException(std::string msg) : runtime_error(msg.c_str()) { }

private:
  string msg;
};


#endif //SFM_IMAGELOADEXCEPTION_H
