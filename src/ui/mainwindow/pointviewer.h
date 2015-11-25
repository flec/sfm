//
// Created by joschi on 25.11.15.
//

#ifndef SFM_POINTVIEWER_H
#define SFM_POINTVIEWER_H

#include <QWidget>
#include <QGLViewer/qglviewer.h>


class PointViewer : public QGLViewer {
Q_OBJECT
public:
  PointViewer(QWidget *parent = 0);

protected :
  virtual void draw();

  virtual void init();

  virtual QString helpString() const;
};


#endif //SFM_POINTVIEWER_H
