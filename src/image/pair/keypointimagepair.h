//
// Pair with keypoint and image
//

#ifndef SFM_KEYPOINTIMAGEPAIR_H
#define SFM_KEYPOINTIMAGEPAIR_H

#include <memory>
#include <opencv2/core/types.hpp>

using namespace std;
using namespace cv;

// forward declaration
class Image;

struct KeyPointImagePair {
public:
  KeyPointImagePair();

  KeyPointImagePair(int keyPointIndex, KeyPoint *keyPoint, shared_ptr<Image> image);

  KeyPointImagePair(int keyPointIndex, shared_ptr<Image> image);

  int keyPointIndex;
  KeyPoint *key_point;
  shared_ptr<Image> image;
};

#endif //SFM_KEYPOINTIMAGEPAIR_H
