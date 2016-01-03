// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <QtWidgets/qfiledialog.h>
#include <iostream>
#include <QtWidgets/qlistview.h>
#include "util/plyutil.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/widgets/cvimagedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sfmapp(SFMApp::getInstance()) {
  ui->setupUi(this);


  connect(this, SIGNAL(imagesUpdated()), ui->featureDetectionTab, SLOT(updateImages()));
  connect(this, SIGNAL(imagePairsUpdated()), ui->matrixFindingTab, SLOT(updateImagePairs()));
  connect(this, SIGNAL(imagePairsUpdated()), ui->featureMatchingTab, SLOT(updateImagePairs()));

  connect(ui->featureMatchingTab, SIGNAL(imagePairsUpdated()), ui->matrixFindingTab, SLOT(updateImagePairs()));
  connect(ui->matrixFindingTab, SIGNAL(imagePairsUpdated()), ui->featureMatchingTab, SLOT(updateImage()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionLoad_images_triggered() {
#ifdef USE_VAR_IMAGES
  sfmapp->loadImages("/var/images/");
#else
  QString images_dir = QFileDialog::getExistingDirectory(this, tr("Choose images directory"), "",
                                                         QFileDialog::ShowDirsOnly);
  QByteArray path = images_dir.toLocal8Bit();
  sfmapp->loadImages(std::string(path.constData(), path.length()) + "/");
#endif
  emit imagesUpdated();
}

void MainWindow::on_actionUnload_Images_triggered() {
  sfmapp->unload();
  emit imagesUpdated();
  emit imagePairsUpdated();
}

void MainWindow::on_actionTest_it_all_triggered() {
  this->on_actionLoad_images_triggered();
  ui->featureDetectionTab->on_detectFeatures_clicked();
  ui->featureMatchingTab->on_matchFeatures_clicked();
  ui->matrixFindingTab->on_findInitialMatrices_clicked();
  ui->triangulationTab->on_runInitialTriangulation_clicked();
  ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_actionTriangulation_QGLViewer_Help_triggered() {
  ui->triangulationTab->showHelp();
}

void MainWindow::on_actionExport_pointcloud_triggered() {
  QString selected_filter;
  QString file_name = QFileDialog::getSaveFileName(this, tr("Export point cloud"), "", PLY_FILES, &selected_filter);

  if (file_name.isNull())
    return;

  QFileInfo file(file_name);
  if (file.suffix().isEmpty())
    file_name.append(".ply");

  QByteArray path = file_name.toLocal8Bit();
  PlyUtil::write(std::string(path.constData(), path.length()), *sfmapp->object_points());
}

void MainWindow::on_actionLoad_Video_triggered()
{
  QString images_dir = QFileDialog::getOpenFileName(this, tr("Choose video file"), "");
  QByteArray path = images_dir.toLocal8Bit();
  sfmapp->loadVideo(std::string(path.constData(), path.length()));

  emit imagesUpdated();
}
