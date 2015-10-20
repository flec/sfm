//
// Created by joschi on 20.10.15.
//

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
