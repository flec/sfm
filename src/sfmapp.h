//
// Created by joschi on 19.10.15.
//

#ifndef SFM_SFMAPP_H
#define SFM_SFMAPP_H

#include "image/image.h"
#include <memory>
#include <image/matches/featurematches.h>
#include <featureDetector/featuredetectorinterface.h>
#include <featureMatcher/featurematcherinterface.h>
#include <featureDetector/ORBFeatureDetector.h>
#include <featureMatcher/FlannFeatureMatcher.h>

using namespace std;

class SFMApp {
private:
  static SFMApp* instance;

  FeatureDetectorInterface* featureDetector = new ORBFeatureDetector();
  FeatureMatcherInterface* featureMatcher = new FlannFeatureMatcher();

  SFMApp() {};

  SFMApp ( const SFMApp& ){};

  ~SFMApp () { }

public:
  static SFMApp* getInstance();

  vector<shared_ptr<Image>> images;

  vector<shared_ptr<FeatureMatches>> featureMatches;

  void detectFeatures();

  void matchFeatures();

  void loadImages(string const &images_dir);

  void unloadImages();
};



#endif //SFM_SFMAPP_H
