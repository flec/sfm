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


  connect(this, SIGNAL(imagesUpdated()), ui->featureDetectionTab, SLOT(updateImages()));
  connect(ui->featureMatchingTab, SIGNAL(matchesUpdated()), ui->matrixFindingTab, SLOT(updateMatches()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionLoad_images_triggered() {
#ifdef _WIN32
  QString images_dir = QFileDialog::getExistingDirectory(this, tr("Choose images directory"), "",
                                                         QFileDialog::ShowDirsOnly);
  sfmapp->loadImages(images_dir.toStdString());
#else
  sfmapp->loadImages("/tmp/images/");
#endif
  emit imagesUpdated();
}

void MainWindow::on_actionUnload_Images_triggered() {
  sfmapp->unloadImages();
  emit imagesUpdated();
}
