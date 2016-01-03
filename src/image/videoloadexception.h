// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_VIDEOLOADEXCEPTION_H
#define SFM_VIDEOLOADEXCEPTION_H

class VideoLoadException : public std::runtime_error {
public:
  VideoLoadException() : runtime_error("Video could not be loaded.") { }

  ~VideoLoadException() throw() { }

  VideoLoadException(std::string msg) : runtime_error(msg.c_str()) { }

private:
  string msg;
};


#endif //SFM_VIDEOLOADEXCEPTION_H
