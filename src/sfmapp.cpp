//
// Created by joschi on 19.10.15.
//

#include <image/imageloader.h>
#include "sfmapp.h"
#include "util/plyutil.h"
#include <iostream>
#include <ctime>

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
  image_pairs.clear();
  object_points.clear();
  feature_detector->detectFeatures(images);
}

void SFMApp::matchFeatures() {
  image_pairs.clear();
  object_points.clear();

  for (unsigned int i = 0; i < images.size() - 1; i++) {
    image_pairs.push_back(feature_matcher->matchFeatures(images.at(i), images.at(i + 1)));
    feature_matcher->filterMatches(image_pairs.back());
  }
}


void SFMApp::findInitialMatrices(shared_ptr<ImagePair> &initial_image_pair, Mat &intristic_camera_paramaters) {
  this->initial_image_pair = initial_image_pair;
  intrinsic_camera_parameters_ = intristic_camera_paramaters;
  // find camera matrix
  cameraMatrixFinder->findCameraMatrix(initial_image_pair, intristic_camera_paramaters);
  // set rotation and translation on images
  initial_image_pair->image1->camera()->set_extrinsic();
  initial_image_pair->image2->camera()->set_extrinsic(initial_image_pair->rotation, initial_image_pair->translation);
  // find projection matrix
  projectionMatrixFinder->findProjectionMatrix(initial_image_pair, intristic_camera_paramaters);
}


void SFMApp::triangulateInitialImagePair() {
  // Clear the current object points
  object_points.clear();

  // clear the matrices except for the initial image pair
  for (auto image_pair:image_pairs)
    if (image_pair != initial_image_pair) {
      // only clear camera two, as
      // a) we don't clear camera two of the initial image pair
      // b) camera one is camera two on prev. image pair
      image_pair->image2->clearObjectPointsAndCamera();
      image_pair->clearMatrices();
    }

  prepareForInitialTriangulation();
  triangulatePoints(initial_image_pair);
}

void SFMApp::triangulateNextImagePair() {
  // get the next not yet triangulated image pair in order
  shared_ptr<ImagePair> next_image_pair;
  for (auto image_pair:image_pairs)
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
  for (auto image_pair : image_pairs) {
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
      object_points.erase(remove(object_points.begin(), object_points.end(), object_point_to_remove),
                          object_points.end());

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
  initial_image_pair->getMatches(initial_image_pair->triangulation_points1,
                                 initial_image_pair->triangulation_points2);
}

void SFMApp::prepareForTriangulation(shared_ptr<ImagePair> image_pair) {
  // find camera matrix and remove outliner matches
  cameraMatrixFinder->findCameraMatrix(image_pair, intrinsic_camera_parameters_);

  // separate points into those for PnP solving and those for triangulation
  vector<KeyPoint> *keypoints1 = image_pair->image1->get_keypoints();
  vector<KeyPoint> *keypoints2 = image_pair->image2->get_keypoints();
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
  pnpSolver->solve(image_pair, intrinsic_camera_parameters_);

  // find projection matrices
  projectionMatrixFinder->findProjectionMatrix(image_pair, intrinsic_camera_parameters_);
}

void SFMApp::triangulatePoints(shared_ptr<ImagePair> image_pair) {
  vector<Point3f> points3Dh;
  triangulator->findPoints3D(image_pair, points3Dh);

  // compute color
  float rand_color = (double) rand() / (RAND_MAX);
  float r = 1.0 - rand_color;
  float g = 0.2f;
  float b = rand_color;

  // create object points
  int c = 0;
  for (auto match:image_pair->matches) {
    shared_ptr<ObjectPoint> objectPoint = image_pair->image1->getObjectPoint(match.queryIdx);
    if (!objectPoint) {
      objectPoint = shared_ptr<ObjectPoint>(
          new ObjectPoint(points3Dh.at(c).x, points3Dh.at(c).y, points3Dh.at(c).z, r, g, b));
      this->object_points.push_back(objectPoint);
      // add references for image1
      objectPoint->addReference(match.queryIdx, image_pair->image1);
      image_pair->image1->addObjectPoint(match.queryIdx, objectPoint);
      //increment column
      c++;
    }
    // add references for image2
    objectPoint->addReference(match.trainIdx, image_pair->image2);
    image_pair->image2->addObjectPoint(match.trainIdx, objectPoint);

  }
}

