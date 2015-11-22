//
// Created by joschi on 22.11.15.
//

#include <opencv2/core.hpp>
#include "hztriangulator.h"
#if 0
void HZTriangulator::findPoints3D(shared_ptr <ImagePair> &image_pair, Mat &points3Dh) {
  vector <cv::Point2f> points1;
  vector <cv::Point2f> points2;

  image_pair->getMatches(points1, points2);
}

/**
 From http://www.morethantechnical.com/2012/01/04/simple-triangulation-with-opencv-from-harley-zisserman-w-code/
 From "Triangulation", Hartley, R.I. and Sturm, P., Computer vision and image understanding, 1997
 */
Mat_<double> HZTriangulator::linearLSTriangulation(Point3d u,       //homogenous image point (u,v,1)
                                           Matx34d P,       //camera 1 matrix
                                           Point3d u1,      //homogenous image point in 2nd camera
                                           Matx34d P1       //camera 2 matrix
) {
  //build matrix A for homogenous equation system Ax = 0
  //assume X = (x,y,z,1), for Linear-LS method
  //which turns it into a AX = B system, where A is 4x3, X is 3x1 and B is 4x1
  Matx43d A(u.x*P(2,0)-P(0,0),	u.x*P(2,1)-P(0,1),		u.x*P(2,2)-P(0,2),
            u.y*P(2,0)-P(1,0),	u.y*P(2,1)-P(1,1),		u.y*P(2,2)-P(1,2),
            u1.x*P1(2,0)-P1(0,0), u1.x*P1(2,1)-P1(0,1),	u1.x*P1(2,2)-P1(0,2),
            u1.y*P1(2,0)-P1(1,0), u1.y*P1(2,1)-P1(1,1),	u1.y*P1(2,2)-P1(1,2)
  );
  Matx41d B(-(u.x*P(2,3)	-P(0,3)),
            -(u.y*P(2,3)	-P(1,3)),
            -(u1.x*P1(2,3)	-P1(0,3)),
            -(u1.y*P1(2,3)	-P1(1,3)));

  Mat_<double> X;
  solve(A,B,X,DECOMP_SVD);


  return X;
}

/**
 From http://www.morethantechnical.com/2012/01/04/simple-triangulation-with-opencv-from-harley-zisserman-w-code/
 */
void HZTriangulator::triangulatePoints(const vector<KeyPoint>& pt_set1,
                                       const vector<KeyPoint>& pt_set2,
                                       const Mat& Kinv,
                                       const Matx34d& P,
                                       const Matx34d& P1,
                                       vector<ObjectPoint>& pointcloud,
                                       vector<KeyPoint>& correspImg1Pt) {
#ifdef __SFM__DEBUG__
  vector depths;
#endif

  pointcloud.clear();
  correspImg1Pt.clear();

  double t = getTickCount();
  unsigned int pts_size = pt_set1.size();
#pragma omp parallel for
  for (int i = 0; i < pts_size; i++) {
    Point2f kp = pt_set1[i];
    Point3d u(kp.x, kp.y, 1.0);
    Mat_ um = Kinv * Mat_(u);
    u = um.at(0);
    Point2f kp1 = pt_set2[i];
    Point3d u1(kp1.x, kp1.y, 1.0);
    Mat_ um1 = Kinv * Mat_(u1);
    u1 = um1.at(0);

    Mat_ X = iterativeLinearLSTriangulation(u, P, u1, P1);

//      if(X(2) > 6 || X(2) < 0) continue;

#pragma omp critical
    {
      pointcloud.push_back(Point3d(X(0), X(1), X(2)));
      correspImg1Pt.push_back(pt_set1[i]);
#ifdef __SFM__DEBUG__
      depths.push_back(X(2));
#endif
    }
  }

  t = ((double) getTickCount() - t) / getTickFrequency();

//show "range image"
#ifdef __SFM__DEBUG__
  {
          double minVal,maxVal;
          minMaxLoc(depths, &minVal, &maxVal);
          Mat tmp(240,320,CV_8UC3); //cvtColor(img_1_orig, tmp, CV_BGR2HSV);
          for (unsigned int i=0; i            double _d = MAX(MIN((pointcloud[i].z-minVal)/(maxVal-minVal),1.0),0.0);
              circle(tmp, correspImg1Pt[i], 1, Scalar(255 * (1.0-(_d)),255,255), CV_FILLED);
          }
          cvtColor(tmp, tmp, CV_HSV2BGR);
          imshow("out", tmp);
          waitKey(0);
          destroyWindow("out");
      }
#endif
}
#endif