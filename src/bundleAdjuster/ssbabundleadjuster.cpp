// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "ssbabundleadjuster.h"

const double SSBABundleAdjuster::OPTIMIZER_TAU = 1e-3;
const int SSBABundleAdjuster::OPTIMIZER_MAX_ITERATIONS = 50;

void SSBABundleAdjuster::adjust(Mat intrinsic_camera_params, vector<shared_ptr<ObjectPoint>> &object_points,
                                vector<shared_ptr<Image>> &images) {

  // prepare data for bundle adjustment
  Matrix3x3d k = convertIntrinsicCameraParams(intrinsic_camera_params);
  Matrix3x3d k_normalized = normalizeIntrinsicCameraParams(k);
  double const inlier_threshold = 2.0 / fabs(k[0][0]);
  StdDistortionFunction distortion;
  vector<Vector3d> object_points_ssba = convertObjectPoints(object_points);
  vector<CameraMatrix> cams = getCameras(images, k);
  vector<Vector2d> measurements;
  vector<int> correspondingView;
  vector<int> correspondingPoint;
  getCorrespondences(object_points, k, measurements, correspondingView, correspondingPoint);

  // create optimizer
  CommonInternalsMetricBundleOptimizer optimizer(V3D::FULL_BUNDLE_FOCAL_LENGTH_PP, inlier_threshold, k_normalized,
                                                 distortion, cams,
                                                 object_points_ssba, measurements, correspondingView,
                                                 correspondingPoint);

  // set optimizer parameters
  optimizer.tau = OPTIMIZER_TAU;
  optimizer.maxIterations = OPTIMIZER_MAX_ITERATIONS;
  // do adjustment
  optimizer.minimize();

  // update data if adjustment is ok
  if (optimizer.status != 2) {
    updateObjectPoints(object_points, object_points_ssba);
    updateCameras(images, cams);
  }
}

Matrix3x3d SSBABundleAdjuster::convertIntrinsicCameraParams(const Mat &matrix) {
  Matrix3x3d cmat;
  makeIdentityMatrix(cmat);
  cmat[0][0] = matrix.at<double>(0, 0);
  cmat[1][1] = matrix.at<double>(1, 1);
  cmat[0][1] = matrix.at<double>(0, 1);
  cmat[0][2] = matrix.at<double>(0, 2);
  cmat[1][2] = matrix.at<double>(1, 2);
  return cmat;
}

Matrix3x3d SSBABundleAdjuster::normalizeIntrinsicCameraParams(const Matrix3x3d &matrix) {
  Matrix3x3d normalized = matrix;
  scaleMatrixIP(1.0 / matrix[0][0], normalized);
  normalized[2][2] = 1.0;
  return normalized;
}

vector<Vector3d> SSBABundleAdjuster::convertObjectPoints(const vector<shared_ptr<ObjectPoint>> &object_points) {
  vector<Vector3d> points(object_points.size());
  for (unsigned int i = 0; i < object_points.size(); ++i) {
    points[i][0] = object_points.at(i)->coordinates()->x;
    points[i][1] = object_points.at(i)->coordinates()->y;
    points[i][2] = object_points.at(i)->coordinates()->z;
  }
  return points;
}

vector<CameraMatrix> SSBABundleAdjuster::getCameras(vector<shared_ptr<Image>> &images, Matrix3x3d &k) {
  vector<CameraMatrix> cams;
  for (unsigned int i = 0; i < images.size(); ++i) {
    Matrix3x3d rotation;
    Vector3d translation;
    Mat_<double> extrinsic = *images.at(i)->camera()->extrinsic();

    // check if image has been triangulated
    if (extrinsic.data == NULL) {
      break;
    }

    // extract rotation
    rotation[0][0] = extrinsic(0, 0);
    rotation[0][1] = extrinsic(0, 1);
    rotation[0][2] = extrinsic(0, 2);
    rotation[1][0] = extrinsic(1, 0);
    rotation[1][1] = extrinsic(1, 1);
    rotation[1][2] = extrinsic(1, 2);
    rotation[2][0] = extrinsic(2, 0);
    rotation[2][1] = extrinsic(2, 1);
    rotation[2][2] = extrinsic(2, 2);

    // extract translation
    translation[0] = extrinsic(0, 3);
    translation[1] = extrinsic(1, 3);
    translation[2] = extrinsic(2, 3);

    // create SSBA camera matrix
    CameraMatrix camera;
    camera.setIntrinsic(k);
    camera.setRotation(rotation);
    camera.setTranslation(translation);
    cams.push_back(camera);

    // set reference in map for correspondences
    image_camera_map[images.at(i)->file_name()] = i;
  }
  return cams;
}

void SSBABundleAdjuster::getCorrespondences(const vector<shared_ptr<ObjectPoint>> &object_points, const Matrix3x3d &k,
                                            vector<Vector2d> &measurements, vector<int> &corresponding_view,
                                            vector<int> &corresponding_point) {
  for (unsigned int i = 0; i < object_points.size(); ++i) {
    // for each 3D point get the corresponding images points
    for (auto reference : *object_points.at(i)->references()) {
      // get image point
      Vector3d image_point;
      Point2f key_point = reference.getKeyPoint()->pt;
      image_point[0] = key_point.x;
      image_point[1] = key_point.y;
      image_point[2] = 1.0;

      // normalize point with focal length and add to vector
      scaleVectorIP(1.0 / k[0][0], image_point);
      measurements.push_back(Vector2d(image_point[0], image_point[1]));

      // set correspondences between image and 3D point
      corresponding_view.push_back(image_camera_map[reference.image()->file_name()]);
      corresponding_point.push_back(i);
    }
  }
}

void SSBABundleAdjuster::updateObjectPoints(vector<shared_ptr<ObjectPoint>> &object_points,
                                            vector<Vector3d> &object_points_ssba) {
  for (unsigned int i = 0; i < object_points.size(); ++i) {
    object_points.at(i)->updateCoordinates(object_points_ssba[i][0], object_points_ssba[i][1],
                                           object_points_ssba[i][2]);
  }
}


void SSBABundleAdjuster::updateCameras(vector<shared_ptr<Image>> &images, vector<CameraMatrix> &cameras) {
  for (unsigned int i = 0; i < cameras.size(); ++i) {
    Matrix3x3d rotation = cameras[i].getRotation();
    Vector3d translation = cameras[i].getTranslation();

    // extract rotation
    Mat cvRotation = (Mat_<double>(3, 3) <<
                      rotation[0][0], rotation[0][1], rotation[0][2],
        rotation[1][0], rotation[1][1], rotation[1][2],
        rotation[2][0], rotation[2][1], rotation[2][2]);

    // extract translation
    Mat cvTranslation = (Mat_<double>(3, 1) << translation[0], translation[1], translation[2]);

    images.at(i)->camera()->set_extrinsic(cvRotation, cvTranslation);
  }
}
