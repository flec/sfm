// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_POINTVIEWER_H
#define SFM_POINTVIEWER_H

#include <QWidget>
#include <QGLViewer/qglviewer.h>
#include <sfmapp.h>
#include <image/camera/imagecamera.h>

using namespace std;
using namespace qglviewer;

class PointViewer : public QGLViewer {
Q_OBJECT
public:
  PointViewer(QWidget *parent = 0);

  void update(vector<shared_ptr<ObjectPoint>> &object_points, vector<shared_ptr<ImageCamera>> &cameras);

  // sets the pivot at the objects center
  void setObjectCenterPivot();

protected :
  virtual void draw();

  virtual QString helpString() const;

private:
  SFMApp *sfmapp;
  vector<shared_ptr<ObjectPoint>> visible_object_points;
  vector<shared_ptr<ImageCamera>> cameras;
};


#endif //SFM_POINTVIEWER_H
