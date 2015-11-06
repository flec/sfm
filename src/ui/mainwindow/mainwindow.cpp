#include <QtWidgets/qfiledialog.h>
#include <iostream>
#include <QtWidgets/qlistview.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sfmapp(SFMApp::getInstance()) {
  ui->setupUi(this);
  featureDetectionTab = this->findChild<FeatureDetectionTab *>("featureDetectionTab");
  featureMatchingTab = this->findChild<FeatureDetectionTab *>("featureMatchingTab");
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionLoad_images_triggered() {
#ifdef _WIN32
  QString images_dir = QFileDialog::getExistingDirectory(this, tr("Choose images directory"), "",
                                                         QFileDialog::ShowDirsOnly);
  QByteArray path = images_dir.toLocal8Bit();
  sfmapp->loadImages(std::string(path.constData(), path.length()) + "/");
#else
  sfmapp->loadImages("/tmp/images/");
#endif

  featureDetectionTab->updateImages();
}

void MainWindow::on_actionUnload_Images_triggered() {
  sfmapp->unloadImages();
  featureDetectionTab->updateImages();
}
