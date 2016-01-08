// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "image/imageloader.h"
#include "image/videoloader.h"
#include "sfmapp.h"
#include <omp.h>

SFMApp *SFMApp::instance = 0;

SFMApp *SFMApp::getInstance() {
  if (!instance)
    instance = new SFMApp();
  return instance;
}

void SFMApp::loadImages(string const &images_dir) {
  images_ = ImageLoader::loadImagesFromDir(images_dir);
  loadParamsAndUndistort();
}

void SFMApp::loadVideo(const string &file_name) {
  images_ = VideoLoader::loadVideoFrames(file_name);
  loadParamsAndUndistort();
}

void SFMApp::unload() {
  images_.clear();
  image_pairs_.clear();
  initial_image_pair_ = NULL;
}

void SFMApp::detectFeatures() {
  image_pairs_.clear();
  object_points_.clear();
  feature_detector_->detectFeatures(images_);
}

void SFMApp::matchFeatures() {
  image_pairs_.clear();
  object_points_.clear();

  // Match keypoints of images in a parallel fashion
#pragma omp parallel
  {
    vector<shared_ptr<ImagePair>> image_pairs_private;
#pragma omp for nowait schedule(static)
    for (int i = 0; i < images_.size() - 1; i++) {
      image_pairs_private.push_back(feature_matcher_->matchFeatures(images_.at(i), images_.at(i + 1)));
      // filtering matches can turn out bad, if we have very very good matches that are used as a reference.
      feature_matcher_->filterMatches(image_pairs_private.back());
    }
#pragma omp for schedule(static) ordered
    for (int i = 0; i < omp_get_num_threads(); i++) {
#pragma omp ordered
      image_pairs_.insert(image_pairs_.end(), image_pairs_private.begin(), image_pairs_private.end());
    }
  }
}

void SFMApp::findInitialMatrices(shared_ptr<ImagePair> &initial_image_pair, Mat &intristic_camera_paramaters) {
  this->initial_image_pair_ = initial_image_pair;
  intrinsic_camera_parameters_ = intristic_camera_paramaters;
  // find camera matrix
  camera_matrix_finder_->findCameraMatrix(initial_image_pair, intristic_camera_paramaters);
  // set rotation and translation on images
  initial_image_pair->image1->camera()->set_extrinsic();
  initial_image_pair->image2->camera()->set_extrinsic(initial_image_pair->rotation, initial_image_pair->translation);
}

void SFMApp::reconstructInitialImagePair() {
  // Clear the current object points
  object_points_.clear();

  // clear the matrices except for the initial image pair
  for (auto image_pair:image_pairs_)
    if (image_pair != initial_image_pair_) {
      // only clear camera two, as
      // a) we don't clear camera two of the initial image pair
      // b) camera one is camera two on prev. image pair, and thus cleared
      image_pair->image2->clearObjectPointsAndCamera();
      image_pair->clearMatrices();
    }

  prepareForInitialTriangulation();
  triangulatePoints(initial_image_pair_);
}

void SFMApp::reconstructNextImagePair() {
  // get the next not yet triangulated image pair in order
  shared_ptr<ImagePair> next_image_pair;
  for (auto image_pair:image_pairs_)
    if (image_pair->rotation.data == NULL) {
      next_image_pair = image_pair;
      break;
    }

  if (next_image_pair) {
    prepareForTriangulation(next_image_pair);
    triangulatePoints(next_image_pair);
  }
}

void SFMApp::removeLastCamera() {
  // get the last triangulated image pair
  shared_ptr<ImagePair> last_triangulated_image_pair;
  for (auto image_pair : image_pairs_) {
    if (image_pair->rotation.data == NULL)
      break;
    last_triangulated_image_pair = image_pair;
  }

  typedef map<int, shared_ptr<ObjectPoint>>::iterator it_type;
  map<int, shared_ptr<ObjectPoint>> *removal_points = last_triangulated_image_pair->image2->object_points();
  for (it_type iterator = removal_points->begin(); iterator != removal_points->end(); iterator++) {
    // iterator->first = key
    // iterator->second = value
    shared_ptr<ObjectPoint> object_point_to_remove = iterator->second;

    // remove reference to image1
    object_point_to_remove->removeReferencesToImage(last_triangulated_image_pair->image2);


    if (object_point_to_remove->getNumReferences() <= 1) {
      // remove object_point_to_remove from global object_points
      object_points_.erase(remove(object_points_.begin(), object_points_.end(), object_point_to_remove),
                           object_points_.end());

      // remove object point from image1
      map<int, shared_ptr<ObjectPoint>> *image1_object_points = last_triangulated_image_pair->image1->object_points();
      for (it_type iterator_img1 = image1_object_points->begin();
           iterator_img1 != image1_object_points->end(); iterator_img1++)
        if (iterator_img1->second == object_point_to_remove)
          last_triangulated_image_pair->image1->removeObjectPoint(iterator_img1->first);
    }
  }
  last_triangulated_image_pair->image2->clearObjectPointsAndCamera();
  last_triangulated_image_pair->clearMatrices();
}

void SFMApp::prepareForInitialTriangulation() {
  initial_image_pair_->getMatches(initial_image_pair_->triangulation_points1,
                                 initial_image_pair_->triangulation_points2);
}

void SFMApp::prepareForTriangulation(shared_ptr<ImagePair> image_pair) {
  // find camera matrix and remove outlier matches
  camera_matrix_finder_->findCameraMatrix(image_pair, intrinsic_camera_parameters_);

  // separate points into those for PnP solving and those for triangulation
  vector<KeyPoint> *keypoints1 = image_pair->image1->keypoints();
  vector<KeyPoint> *keypoints2 = image_pair->image2->keypoints();
  for (auto match:image_pair->matches) {
    shared_ptr<ObjectPoint> objectPoint = image_pair->image1->getObjectPoint(match.queryIdx);
    if (objectPoint) {
      image_pair->pnp_object_points.push_back(*objectPoint->coordinates());
      image_pair->pnp_image_points.push_back(keypoints2->at(match.trainIdx).pt);
    } else {
      image_pair->triangulation_points1.push_back(keypoints1->at(match.queryIdx).pt);
      image_pair->triangulation_points2.push_back(keypoints2->at(match.trainIdx).pt);
    }
  }

  // solve PnP
  pnp_solver_->solve(image_pair, intrinsic_camera_parameters_);
}

void SFMApp::triangulatePoints(shared_ptr<ImagePair> image_pair) {
  map<int, Point3f> map_points3D;
  triangulator_->findPoints3D(image_pair, intrinsic_camera_parameters_, map_points3D);

  // create object points
  int c = 0;
  for (auto match:image_pair->matches) {
    shared_ptr<ObjectPoint> objectPoint = image_pair->image1->getObjectPoint(match.queryIdx);
    if (!objectPoint) {
      map<int, Point3f>::iterator points3D_entry = map_points3D.find(c++);
      if (points3D_entry != map_points3D.end()) {
        objectPoint = shared_ptr<ObjectPoint>(
            new ObjectPoint(points3D_entry->second.x, points3D_entry->second.y, points3D_entry->second.z));
        this->object_points_.push_back(objectPoint);
        // add references for image1
        objectPoint->addReference(match.queryIdx, image_pair->image1);
        image_pair->image1->addObjectPoint(match.queryIdx, objectPoint);
      }
    }

    // add references for image2
    if (objectPoint) {
      objectPoint->addReference(match.trainIdx, image_pair->image2);
      image_pair->image2->addObjectPoint(match.trainIdx, objectPoint);
    }
  }
}

void SFMApp::doBundleAdjustment() {
  bundle_adjuster_->adjust(intrinsic_camera_parameters_, object_points_, images_);
}

void SFMApp::doDenseReconstructon() {
  dense_reconstructor_->reconstruct(image_pairs_);
}

void SFMApp::loadCameraParameters(const string &dir_path) {
  ParameterLoader::load(dir_path, intrinsic_camera_parameters_, camera_distortion_coefficients_);
}

void SFMApp::undistortImages() {
  if (intrinsic_camera_parameters_.data != NULL && camera_distortion_coefficients_.data != NULL) {
    ImageUndistorter::undistort(images_, intrinsic_camera_parameters_, camera_distortion_coefficients_);
  }
}

void SFMApp::loadParamsAndUndistort() {
  if (images_.size() > 0) {
    loadCameraParameters(images_.at(0)->file_path());
    undistortImages();
  }
}
