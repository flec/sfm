//
// Created by joschi on 25.11.15.
//

#ifndef SFM_POINTVIEWER_H
#define SFM_POINTVIEWER_H

#include <QWidget>
#include <QGLViewer/qglviewer.h>
#include <sfmapp.h>

using namespace std;
using namespace qglviewer;

class PointViewer : public QGLViewer {
Q_OBJECT
public:
  PointViewer(QWidget *parent = 0);
  void update(vector<shared_ptr<ObjectPoint>> &object_points);

protected :
  virtual void draw();

  virtual QString helpString() const;

private:
  SFMApp *sfmapp;
  shared_ptr<vector<shared_ptr<ObjectPoint>>> visible_object_points;
};


#endif //SFM_POINTVIEWER_H
