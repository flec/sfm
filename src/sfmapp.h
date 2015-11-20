//
// Created by joschi on 19.10.15.
//

#ifndef SFM_SFMAPP_H
#define SFM_SFMAPP_H

#include "image/image.h"
#include <memory>
#include <cameraMatrixFinder/cameramatrixfinder.h>
#include "cameraMatrixFinder/ransaccameramatrixfinder.h"
#include <featureDetector/kazefeaturedetector.h>
#include <featureDetector/orbfeaturedetector.h>
#include <featureDetector/siftfeaturedetector.h>
#include "projectionMatrixFinder/cvprojectionmatrixfinder.h"
#include "image/pair/imagepair.h"
#include "featureDetector/featuredetector.h"
#include "featureMatcher/featurematcher.h"
#include "featureMatcher/flannfeaturematcher.h"
#include "triangulator/basetriangulator.h"

using namespace std;

/*
 * This class provides the overall logic and is either triggered by the GUI or the CLI
 */
class SFMApp {
private:
  static SFMApp* instance;

  FeatureDetecter* feature_detector = new KAZEFeatureDetector(); // init feature detector
  FeatureMatcher*feature_matcher = new FlannFeatureMatcher(); // init feature matcher
  CameraMatrixFinder *cameraMatrixFinder = new RANSACCameraMatrixFinder();  // camera matrix finder for initial matirx
  ProjectionMatrixFinder *projectionMatrixFinder = new CvProjectionMatrixFinder(); // projection matrix finder
  Triangulator *triangulator = new BaseTriangulator();

  shared_ptr<ImagePair> initial_image_pair; // initial image pair

  Mat intrinsic_camera_parameters_;  // intrinsic camera parameters

  SFMApp() {};

  SFMApp ( const SFMApp& ){};

  ~SFMApp () { }

public:
  static SFMApp* getInstance();

  // Images that have been loaded by 'loadImages()'
  vector<shared_ptr<Image>> images;

  // Pairs of images with the corresponding matches
  vector<shared_ptr<ImagePair>> image_pairs;

  // Detect features of the loaded images
  void detectFeatures();

  // Match the features between the loaded images. Each image is matched against each other image.
  // The resulting image pairs are stored in 'image_pairs'
  void matchFeatures();

  // Find the initial matrices of an image pair.
  void findInitialMatrices(shared_ptr<ImagePair> &initial_image_pair, Mat& intristic_camera_paramaters);

  // Load images from a directory into 'images'
  void loadImages(string const &images_dir);

  // Unload everything
  void unload();

  Mat* intrinsic_camera_parameters(){
    return &intrinsic_camera_parameters_;
  }

  // Triangulates the points of the initial image pair
  void triangulateInitialPoints();

  // Triangulates points of an image pair
  void triangulatePoints(shared_ptr<ImagePair> image_pair);
};



#endif //SFM_SFMAPP_H
