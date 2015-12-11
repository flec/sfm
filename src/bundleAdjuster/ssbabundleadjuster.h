// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#ifndef SFM_SSBABUNDLEADJUSTER_H
#define SFM_SSBABUNDLEADJUSTER_H

#include <map>
#include "bundleadjuster.h"
#include "SSBA-4.0/Math/v3d_linear.h"
#include "SSBA-4.0/Base/v3d_vrmlio.h"
#include "SSBA-4.0/Geometry/v3d_metricbundle.h"

using namespace V3D;

/**
 * Implementation of bundle adjuster using the SSBA library
 */
class SSBABundleAdjuster : public BundleAdjuster {
private:
  /**
   * maps images to cameras (image name to camera index)
   */
  map<string, int> image_camera_map;

  /**
   * converts intrinsic camera parameters from OpenCV to SSBA form
   *
   * matrix   matrix with intrinsic camera parameters
   * returns  converted intrinsic camera parameters
   */
  Matrix3x3d convertIntrinsicCameraParams(const Mat &matrix);

  /**
   * normalizes the intrinsic camera parameters
   *
   * matrix   matrix with intrinsic camera parameters
   * returns  normalized intrinsic camera parameters
   */
  Matrix3x3d normalizeIntrinsicCameraParams(const Matrix3x3d &matrix);

  /**
   * converts object points to SSBA form
   *
   * object_points  3D points as ObjectPoint objects
   * returns        3D points in SSBA form
   */
  vector<Vector3d> convertObjectPoints(const vector<shared_ptr<ObjectPoint>> &object_points);

  /**
   * extracts the cameras from the given images and creates cameras for using in SSBA
   *
   * images   vector of images used for the SSBA process
   * k        intrinsic camera parameters in SSBA form
   * returns  vector of camera matrices used for the SSBA process
   */
  vector<CameraMatrix> getCameras(vector<shared_ptr<Image>> &images, Matrix3x3d &k);

  /**
   * Returns the correspondences between image points and object points in SSBA form
   *
   * object_points        3D points as ObjectPoint objects
   * k                    intrinsic camera parameters in SSBA form
   * measurements         output: normalized positions of image points
   * corresponding_view   output: indices of images corresponding to the indices of corresponding_point
   * corresponding_point  output: indices of 3D points corresponding to the indices of corresponding_view
   */
  void getCorrespondences(const vector<shared_ptr<ObjectPoint>> &object_points, const Matrix3x3d &k,
                          vector<Vector2d> &measurements, vector<int> &corresponding_view,
                          vector<int> &corresponding_point);

  /**
   * Updates the coordinates of the existing 3D points with the adjusted points
   *
   * object_points      existing 3D points
   * object_points_ssba adjusted 3D points
   */
  void updateObjectPoints(vector<shared_ptr<ObjectPoint>> &object_points, vector<Vector3d> &object_points_ssba);

  /**
   * Updates the position of the cameras with the coordinates of the adjusted cameras
   *
   * images   images used in the SSBA process containing the corresponding camera
   * cameras  cameras from the SSBA process with adjusted position
   */
  void updateCameras(vector<shared_ptr<Image>> &images, vector<CameraMatrix> &cameras);

public:
  /**
   * @see BundleAdjuster
   */
  void adjust(Mat intrinsic_camera_params, vector<shared_ptr<ObjectPoint>> &object_points,
              vector<shared_ptr<Image>> &images);

};

#endif //SFM_SSBABUNDLEADJUSTER_H
