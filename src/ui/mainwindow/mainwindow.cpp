#include <QtWidgets/qfiledialog.h>
#include <iostream>
#include <QtWidgets/qlistview.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);
  featureDetectionTab = this->findChild<FeatureDetectionTab *>("featureDetectionTab");
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionLoad_images_triggered() {
  QString images_dir = QFileDialog::getExistingDirectory(this, tr("Choose images directory"), "",
                                                         QFileDialog::ShowDirsOnly);
  sfmapp = new SFMApp(images_dir.toStdString() + "/");
  //sfmapp = new SFMApp("/tmp/temple/");

  featureDetectionTab->updateImages(&sfmapp->images);
}

void MainWindow::on_actionUnload_Images_triggered() {
  sfmapp->unloadImages();
  featureDetectionTab->updateImages(&sfmapp->images);
}
