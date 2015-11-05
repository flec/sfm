//
// Created by joschi on 19.10.15.
//

#ifndef SFM_SFMAPP_H
#define SFM_SFMAPP_H

#include "image/image.h"
#include <memory>
#include <cameraMatrixFinder/cameramatrixfinder.h>
#include <cameraMatrixFinder/RANSACCameraMatrixFinder.h>
#include "image/pair/imagepair.h"
#include "featureDetector/featuredetector.h"
#include "featureMatcher/featurematcher.h"
#include "featureDetector/orbfeaturedetector.h"
#include "featureMatcher/flannfeaturematcher.h"

using namespace std;

class SFMApp {
private:
  static SFMApp* instance;

  FeatureDetecter* featureDetector = new ORBFeatureDetector();
  FeatureMatcher* featureMatcher = new FlannFeatureMatcher();
  CameraMatrixFinder *cameraMatrixFinder = new RANSACCameraMatrixFinder();

  SFMApp() {};

  SFMApp ( const SFMApp& ){};

  ~SFMApp () { }

public:
  static SFMApp* getInstance();

  vector<shared_ptr<Image>> images;

  vector<shared_ptr<ImagePair>> image_pairs;

  void detectFeatures();

  void matchFeatures();

  void findMatrices();

  void loadImages(string const &images_dir);

  void unloadImages();
};



#endif //SFM_SFMAPP_H
