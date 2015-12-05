//
// Created by marco on 02.12.15.
//



#include "ssbabundleadjuster.h"

void SSBABundleAdjuster::adjust(Mat intrinsicCameraParams, vector<shared_ptr<ObjectPoint>> objectPoints,
                                vector<shared_ptr<Image>> images) {

  // prepare data for bundle adjustment
  Matrix3x3d K = convertIntrinsicCameraParams(intrinsicCameraParams);
  double const inlierThreshold = 2.0 / fabs(K[0][0]);
  StdDistortionFunction distortion;
  vector<Vector3d> Xs = convertObjectPoints(objectPoints);
  vector<CameraMatrix> cams = getCameras(images, K);
  vector<Vector2d > measurements;
  vector<int> correspondingView;
  vector<int> correspondingPoint;
  getCorrespondences(objectPoints, K, measurements, correspondingView, correspondingPoint);

  // do adjustment
  CommonInternalsMetricBundleOptimizer optimizer(V3D::FULL_BUNDLE_FOCAL_LENGTH_PP, inlierThreshold, K, distortion, cams,
                                                 Xs, measurements, correspondingView, correspondingPoint);

  optimizer.tau = 1e-3;
  optimizer.maxIterations = 50;
  // use this line when it compiles
#if 0
  optimizer.minimize();
#endif

  // update data if adjustment is ok
  if (optimizer.status != 2) {
    updateObjectPoints(objectPoints, Xs);
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

vector<Vector3d> SSBABundleAdjuster::convertObjectPoints(const vector<shared_ptr<ObjectPoint>> objectPoints) {
  vector<Vector3d> points(objectPoints.size());
  int i = 0;
  for (auto objectPoint : objectPoints) {
    points[i][0] = objectPoint->coordinates()->x;
    points[i][1] = objectPoint->coordinates()->y;
    points[i][2] = objectPoint->coordinates()->z;
    i++;
  }
  return points;
}

vector<CameraMatrix> SSBABundleAdjuster::getCameras(vector<shared_ptr<Image>> images, Matrix3x3d K) {
  Matrix3x3d Knorm = normalizeIntrinsicCameraParams(K);
  vector<CameraMatrix> cams(images.size());
  int i = 0;
  for (auto image : images) {
    Matrix3x3d rotation;
    Vector3d translation;
    Mat_<double> extrinsic = *image->camera()->extrinsic();

    rotation[0][0] = extrinsic(0,0);
    rotation[0][1] = extrinsic(0,1);
    rotation[0][2] = extrinsic(0,2);
    rotation[1][0] = extrinsic(1,0);
    rotation[1][1] = extrinsic(1,1);
    rotation[1][2] = extrinsic(1,2);
    rotation[2][0] = extrinsic(2,0);
    rotation[2][1] = extrinsic(2,1);
    rotation[2][2] = extrinsic(2,2);

    translation[0] = extrinsic(0,3);
    translation[1] = extrinsic(1,3);
    translation[2] = extrinsic(2,3);

    cams[i].setIntrinsic(Knorm);
    cams[i].setRotation(rotation);
    cams[i].setTranslation(translation);

    // set reference in map
    image_camera_map[image->file_name()] = i;

    i++;
  }
  return cams;
}

void SSBABundleAdjuster::getCorrespondences(const vector<shared_ptr<ObjectPoint>> objectPoints, const Matrix3x3d &K,
                                            vector<Vector2d> &measurements, vector<int> &correspondingView,
                                            vector<int> &correspondingPoint) {
  int i = 0;
  for (auto objectPoint : objectPoints) {
    for (auto reference : *objectPoint->references()) {
      Vector3d imagePoint;
      Point2f keyPoint = reference.key_point->pt;
      imagePoint[0] = keyPoint.x;
      imagePoint[1] = keyPoint.y;
      imagePoint[2] = 1.0;

      scaleVectorIP(1.0/K[0][0], imagePoint); // normalize with focal length
      measurements.push_back(Vector2d(imagePoint[0], imagePoint[1]));
      correspondingView.push_back(image_camera_map[reference.image->file_name()]);
      correspondingPoint.push_back(i);
    }
    i++;
  }
}

void SSBABundleAdjuster::updateObjectPoints(vector<shared_ptr<ObjectPoint>> objectPoints, vector<Vector3d> Xs) {
  int i = 0;
  for (auto objectPoint : objectPoints) {
    objectPoint->updateCoordinates(Xs[i][0], Xs[i][1], Xs[i][2]);
  }
}


void SSBABundleAdjuster::updateCameras(vector<shared_ptr<Image>> images, vector<CameraMatrix> cameras) {
  for (unsigned int i = 0; i < cameras.size(); ++i) {
    Matrix3x3d rotation = cameras[i].getRotation();
    Vector3d translation = cameras[i].getTranslation();

    Mat cvRotation = (Mat_<double>(3, 3) <<
                  rotation(0, 0), rotation(0, 1), rotation(0, 2),
        rotation(1, 0), rotation(1, 1), rotation(1, 2),
        rotation(2, 0), rotation(2, 1), rotation(2, 2));

    Mat cvTranslation = (Mat_<double>(3, 1) << translation(0), translation(1), translation(2));


    images.at(i)->camera()->set_extrinsic(cvRotation, cvTranslation);
  }
}
