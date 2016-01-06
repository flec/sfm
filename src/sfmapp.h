// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_SFMAPP_H
#define SFM_SFMAPP_H

#include "image/image.h"
#include <memory>
#include <cameraMatrixFinder/cameramatrixfinder.h>
#include "cameraMatrixFinder/ransaccameramatrixfinder.h"
#include "featureDetector/kazefeaturedetector.h"
#include "featureDetector/orbfeaturedetector.h"
#include "featureDetector/siftfeaturedetector.h"
#include "featureDetector/surffeaturedetector.h"
#include "featureDetector/surfcudafeaturedetector.h"
#include "featureDetector/briskfeaturedetector.h"
#include "featureDetector/cornermineigenvalfeaturedetector.h"
#include "projectionMatrixFinder/basicprojectionmatrixfinder.h"
#include "image/pair/imagepair.h"
#include "featureMatcher/flannfeaturematcher.h"
#include "featureMatcher/bffeaturematcher.h"
#include "featureMatcher/opticalflowfeaturematcher.h"
#include "image/objectPoint/objectpoint.h"
#include "triangulator/cvtriangulator.h"
#include "pnpSolver/ransacpnpsolver.h"
#include "bundleAdjuster/ssbabundleadjuster.h"
#include "denseReconstructor/patchdensereconstructor.h"
#include "denseReconstructor/densereconstructor.h"

using namespace std;

/*
 * This class provides the overall logic and is either triggered by the GUI or the CLI.
 * It is a singleton and a reference can be gotten by SFMApp::getInstance()
 */
class SFMApp {
private:
  // Reference to the single instance of itself
  static SFMApp *instance;

  // Initialize the FeatureDetecter
#ifdef USE_CUDA
  FeatureDetecter *feature_detector_ = new SURFCUDAFeatureDetector();
#else
  FeatureDetecter *feature_detector_ = new SURFFeatureDetector();
#endif

  // Initialize the FeatureMatcher
  FeatureMatcher *feature_matcher_ = new FlannFeatureMatcher();

  // Initialize the CameraMatrixFinder
  CameraMatrixFinder *camera_matrix_finder_ = new RANSACCameraMatrixFinder();

  // Initialize the ProjectionMatrixFinder
  ProjectionMatrixFinder *projection_matrix_finder_ = new BasicProjectionMatrixFinder();

  // Initialize the Triangulator
  Triangulator *triangulator_ = new CVTriangulator();

  // Initialize the PnPSolver
  PnPSolver *pnp_solver_ = new RANSACPnPSolver();

  // Initialize the BundleAdjuster
  BundleAdjuster *bundle_adjuster_ = new SSBABundleAdjuster();

  // Initialize the DenseReconstructor
  DenseReconstructor *dense_reconstructor_ = new PatchDenseReconstructor();

  // This is a pointer to the initial image pair. The initial image pair
  // is the one, for which the camera matrices are calculated at first, and on which, then the whole
  // SFM reconstruction sets up.
  shared_ptr<ImagePair> initial_image_pair_;

  // Intrinsic parameters of the camera. Currently only a camera with the same intrinsic parameters is supported.
  Mat intrinsic_camera_parameters_;

  // List of all images
  // !!! Order is important, as only an image pair of the images next to each other will be built.
  vector<shared_ptr<Image>> images_;

  // List of all image pairs
  // !!! Order is important, as image2 in ImagePairA is image2 in ImagePairB.
  vector<shared_ptr<ImagePair>> image_pairs_;

  // A list containing all calculated 3D points. This list is used to draw the point cloud.
  vector<shared_ptr<ObjectPoint>> object_points_;

  /**
   * Private constructor, as it is a singleton, prevent external initialization
   */
  SFMApp() { };

  /**
   * Private copy constructor, as it is a singleton, prevent external initialization
   */
  SFMApp(const SFMApp &) { };

  /**
   * Private destructor, as it is a singleton, prevent external destruction
   */
  ~SFMApp() { }

  void prepareForInitialTriangulation();

  // Prepares the image pair for the triangulation process
  void prepareForTriangulation(shared_ptr<ImagePair> image_pair);

  // Triangulates points of an image pair
  void triangulatePoints(shared_ptr<ImagePair> image_pair);

public:
  /**
   * Return a reference to the single instance. If it does not yet exist, create it.
   */
  static SFMApp *getInstance();

  /**
   * Load all images that are in a certain directory into the images_ vector.
   *
   * images_dir   directory that contains the images
   */
  void loadImages(string const &images_dir);

  /**
   * Loads the frames form a video file
   *
   * file_name  Videos file name
   */
  void loadVideo(const string &file_name);

  /**
   * Detect the features of all loaded images. To load the images, see @loadImages()
   */
  void detectFeatures();

  /**
   * Match the features of all loaded images. Features must have been calculated first - @see detectFeatures()
   */
  void matchFeatures();

  /**
   * Find the matrices of the initial image pair. Those are the base of the whole SFM reconstruction process.
   * Features must have been matched first - @see matchFeatures()
   */
  void findInitialMatrices(shared_ptr<ImagePair> &initial_image_pair, Mat &intristic_camera_paramaters);

  /**
   * Reconstruct the initial image pair - ie the first two images/the first ImagePair.
   * This relies only on the camera matrices (rotation, translation, essential) that are saved in the ImagePair.
   */
  void reconstructInitialImagePair();

  /**
   * Reconstruct the next ImagePair in order - the next, not yet reconstructed, ImagePair in the image_pairs vector.
   * This is done by solving the PnP problem based on the initially reconstructed ImagePair.
   */
  void reconstructNextImagePair();

  /**
   * Remove the last reconstructed camera.
   * Naturally this function removes as well the object points.
   */
  void removeLastCamera();

  /**
   * Optimize the camera position so that the overall mean reprojection error is minimized.
   */
  void doBundleAdjustment();

  /**
   * Not yet implemented
   */
  void doDenseReconstructon();

  /**
   * Unload everything, so that one can load a new set of images, and start the SFM process with those.
   */
  void unload();


  //
  // getters / setters
  //

  vector<shared_ptr<Image>> *images() {return &images_;}

  vector<shared_ptr<ImagePair>> *image_pairs() {return &image_pairs_;}

  vector<shared_ptr<ObjectPoint>> *object_points() { return &object_points_; }

  Mat *intrinsic_camera_parameters() { return &intrinsic_camera_parameters_; }

  ProjectionMatrixFinder *projection_matrix_finder() { return projection_matrix_finder_;}
};


#endif //SFM_SFMAPP_H
