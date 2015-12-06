//
// Created by marco on 02.12.15.
//

#ifndef SFM_SSBABUNDLEADJUSTER_H
#define SFM_SSBABUNDLEADJUSTER_H

#include <map>
#include "bundleadjuster.h"
#include "SSBA-4.0/Math/v3d_linear.h"
#include "SSBA-4.0/Base/v3d_vrmlio.h"
#include "SSBA-4.0/Geometry/v3d_metricbundle.h"

using namespace V3D;

class SSBABundleAdjuster : public BundleAdjuster {
private:
  map<string, int> image_camera_map;

  Matrix3x3d convertIntrinsicCameraParams(const Mat &matrix);

  Matrix3x3d normalizeIntrinsicCameraParams(const Matrix3x3d &matrix);

  vector<Vector3d> convertObjectPoints(const vector<shared_ptr<ObjectPoint>> objectPoints);

  vector<CameraMatrix> getCameras(vector<shared_ptr<Image>> images, Matrix3x3d K);

  void getCorrespondences(const vector<shared_ptr<ObjectPoint>> objectPoints, const Matrix3x3d &K,
                          vector<Vector2d> &measurements, vector<int> &correspondingView,
                          vector<int> &correspondingPoint);

  void updateObjectPoints(vector<shared_ptr<ObjectPoint>> objectPoints, vector<Vector3d> Xs);

  void updateCameras(vector<shared_ptr<Image>> images, vector<CameraMatrix> cameras);

public:
  void adjust(Mat intrinsicCameraParams, vector<shared_ptr<ObjectPoint>> objectPoints,
              vector<shared_ptr<Image>> images);

};

#endif //SFM_SSBABUNDLEADJUSTER_H
