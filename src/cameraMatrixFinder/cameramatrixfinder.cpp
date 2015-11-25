//
// Created by joschi on 05.11.15.
//

#include "cameramatrixfinder.h"

void CameraMatrixFinder::removeOutlinerMatches(shared_ptr<ImagePair> &image_pair, Mat &inliners) {
  int count = 0;
  auto i = begin(image_pair->matches);
  while (i != end(image_pair->matches)) {
    if (inliners.at<char>(count++) == 0) {
      i = image_pair->matches.erase(i);
    }
    else
      ++i;
  }
}