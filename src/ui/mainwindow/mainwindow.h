// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define PLY_FILES "PLY files (*.ply)"

#include <QMainWindow>
#include <sfmapp.h>
#include "featuredetectiontab.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

private:
  Ui::MainWindow *ui;
  SFMApp *sfmapp;

public:
  explicit MainWindow(QWidget *parent = 0);

  ~MainWindow();

private slots:
  void on_actionLoad_images_triggered();

  void on_actionUnload_Images_triggered();

  void on_actionTest_it_all_triggered();

  void on_actionTriangulation_QGLViewer_Help_triggered();

  void on_actionExport_pointcloud_triggered();

signals:
  void imagesUpdated();
  void imagePairsUpdated();

};

#endif // MAINWINDOW_H
