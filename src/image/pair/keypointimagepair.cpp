//
// Created by marco on 04.12.15.
//

#include "keypointimagepair.h"
#include "image/image.h"

KeyPointImagePair::KeyPointImagePair() { }

KeyPointImagePair::KeyPointImagePair(int keyPointIndex, KeyPoint *keyPoint, shared_ptr<Image> image) :
    keyPointIndex(keyPointIndex), key_point(keyPoint), image(image) {

}

KeyPointImagePair::KeyPointImagePair(int keyPointIndex, shared_ptr<Image> image) :
    keyPointIndex(keyPointIndex), image(image) {
  key_point = &image->get_keypoints()->at(keyPointIndex);
}