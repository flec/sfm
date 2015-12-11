// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "cvtriangulator.h"
#include <opencv2/calib3d.hpp>
#include <iostream>
#include "math.h"

using namespace std;
using namespace cv;

const float CVTriangulator::MAX_REPROJECTION_ERROR = 1.5;

void CVTriangulator::findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &intrinsic_camera_parameters,
                                  map<int, Point3f> &map_points3D) {
  Mat mat_points3d;
  vector<Point3f> points3D;
  triangulatePoints(*image_pair->image1->camera()->projection(), *image_pair->image2->camera()->projection(),
  image_pair->triangulation_points1, image_pair->triangulation_points2, mat_points3d);

  // Since it's homogenous (x, y, z, w) coord, divide by w to get (x, y, z, 1)
  mat_points3d.row(0) = (mat_points3d.row(0) / mat_points3d.row(3)) + 0;
  mat_points3d.row(1) = (mat_points3d.row(1) / mat_points3d.row(3)) + 0;
  mat_points3d.row(2) = (mat_points3d.row(2) / mat_points3d.row(3)) + 0;

  // convert mat_points3d into vector<Point3f> for projectPoints
  for (int i = 0; i < mat_points3d.cols; i++)
    points3D.push_back(
        Point3f(mat_points3d.at<float>(0, i), mat_points3d.at<float>(1, i), mat_points3d.at<float>(2, i)));

  // Reproject points to 2D, so we can afterwards calculate the reprojection error
  vector<Point2f> reprojected_points;
  projectPoints(points3D, image_pair->image2->camera()->extrinsic_rotation(),
                image_pair->image2->camera()->extrinsic_translation(), intrinsic_camera_parameters, noArray(),
                reprojected_points);

  // Only add points with acceptable reproj. error
  for (int i = 0; i < mat_points3d.cols; i++) {
    float repojection_error = sqrt(pow(reprojected_points.at(i).x - image_pair->triangulation_points2.at(i).x, 2) +
                                   pow(reprojected_points.at(i).y - image_pair->triangulation_points2.at(i).y, 2));

    if (repojection_error < MAX_REPROJECTION_ERROR)
      map_points3D[i] = Point3f(mat_points3d.at<float>(0, i), mat_points3d.at<float>(1, i),
                                mat_points3d.at<float>(2, i));
  }

#ifdef DEBUG
  printf("Filtered out %lu bad objects points (reprojection error > %f), kept %lu pairs.\n",
         points3D.size() - map_points3D.size(), MAX_REPROJECTION_ERROR,
         map_points3D.size());
#endif
}