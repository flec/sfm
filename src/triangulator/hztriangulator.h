//
// Created by joschi on 22.11.15.
//

#ifndef SFM_HZTRIANGULATOR_H
#define SFM_HZTRIANGULATOR_H


#include "triangulator.h"

class HZTriangulator : public Triangulator {
private:
  void triangulatePoints(const vector<KeyPoint>& pt_set1,
                         const vector<KeyPoint>& pt_set2,
                         const Mat& Kinv,
                         const Matx34d& P,
                         const Matx34d& P1,
                         vector<ObjectPoint>& pointcloud,
                         vector<KeyPoint>& correspImg1Pt);

  Mat_<double> linearLSTriangulation(Point3d u,       //homogenous image point (u,v,1)
                             Matx34d P,       //camera 1 matrix
                             Point3d u1,      //homogenous image point in 2nd camera
                             Matx34d P1       //camera 2 matrix
  );

public:
  void findPoints3D(shared_ptr<ImagePair> &image_pair, Mat &points3Dh);
};


#endif //SFM_HZTRIANGULATOR_H
