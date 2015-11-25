//
// Created by joschi on 19.10.15.
//

#include <image/imageloader.h>
#include "sfmapp.h"
#include "util/plyutil.h"

SFMApp *SFMApp::getInstance() {
  if (!instance)
    instance = new SFMApp();
  return instance;
}

SFMApp *SFMApp::instance = 0;

void SFMApp::loadImages(string const &images_dir) {
  images = ImageLoader::loadImagesFromDir(images_dir);
}

void SFMApp::unload() {
  images.clear();
  image_pairs.clear();
  initial_image_pair = NULL;
}

void SFMApp::detectFeatures() {
  feature_detector->detectFeatures(images);
}

void SFMApp::matchFeatures() {
  image_pairs.clear();
  for (unsigned int i = 0; i < images.size(); i++) {
    for (unsigned int j = i + 1; j < images.size(); j++) {
      image_pairs.push_back(feature_matcher->matchFeatures(images.at(i), images.at(j)));
      feature_matcher->filterMatches(image_pairs.back());
    }
  }
}


void SFMApp::findInitialMatrices(shared_ptr<ImagePair> &initial_image_pair, Mat &intristic_camera_paramaters) {
  this->initial_image_pair = initial_image_pair;
  this->intrinsic_camera_parameters_ = intristic_camera_paramaters;
  cameraMatrixFinder->findCameraMatrix(initial_image_pair, intristic_camera_paramaters);
  projectionMatrixFinder->findProjectionMatrix(initial_image_pair, intristic_camera_paramaters);
}


void SFMApp::triangulatePoints(shared_ptr<ImagePair> image_pair) {
  Mat points3Dh;
  triangulator->findPoints3D(image_pair, points3Dh);

  // create object points
  int c = 0;
  for (auto match:image_pair->matches) {
    shared_ptr<ObjectPoint> objectPoint (new ObjectPoint(points3Dh.at<float>(0, c), points3Dh.at<float>(1, c), points3Dh.at<float>(2, c)));
    this->objectPoints.push_back(objectPoint);
    // add references to images
    objectPoint->addReference(match.queryIdx, image_pair->image1);
    objectPoint->addReference(match.trainIdx, image_pair->image2);
    // add references on image
    image_pair->image1->addObjectPoint(match.queryIdx, objectPoint);
    image_pair->image2->addObjectPoint(match.trainIdx, objectPoint);
    //increment column
    c++;
  }
}

void SFMApp::triangulateInitial() {
  objectPoints.clear();
  prepareForInitialTriangulation();
  triangulatePoints(initial_image_pair);
  PlyUtil::write("/tmp/initialPoints.ply", objectPoints);
}

void SFMApp::triangulateNext(int image_pair_index) {
  shared_ptr<ImagePair> image_pair = image_pairs[image_pair_index];
  prepareForTriangulation(image_pair);
  triangulatePoints(image_pair);
  PlyUtil::write("/tmp/nextPoints.ply", objectPoints);
}

void SFMApp::prepareForInitialTriangulation() {
  initial_image_pair->getMatches(initial_image_pair->triangulation_points1, initial_image_pair->triangulation_points2);
}

void SFMApp::prepareForTriangulation(shared_ptr<ImagePair> image_pair) {
  // separate points into those for PnP solving and those for triangulation
  vector<KeyPoint> *keypoints1 = image_pair->image1->get_keypoints();
  vector<KeyPoint> *keypoints2 = image_pair->image2->get_keypoints();
  for (auto match:image_pair->matches) {
    shared_ptr<ObjectPoint> objectPoint = image_pair->image1->getObjectPoint(match.queryIdx);
    if (objectPoint) {
      image_pair->pnp_object_points.push_back(*objectPoint->getCoordinates());
      image_pair->pnp_image_points.push_back(keypoints2->at(match.trainIdx).pt);
    } else {
      image_pair->triangulation_points1.push_back(keypoints1->at(match.queryIdx).pt);
      image_pair->pnp_image_points.push_back(keypoints2->at(match.trainIdx).pt);
    }
  }

  // solve PnP
  pnpSolver->solve(image_pair, intrinsic_camera_parameters_);
}