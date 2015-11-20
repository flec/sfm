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
  connect(this, SIGNAL(imagePairsUpdated()), ui->matrixFindingTab, SLOT(updateImagePairs()));
  connect(this, SIGNAL(imagePairsUpdated()), ui->featureMatchingTab, SLOT(updateImagePairs()));

  connect(ui->featureMatchingTab, SIGNAL(imagePairsUpdated()), ui->matrixFindingTab, SLOT(updateImagePairs()));

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
  sfmapp->loadImages("/var/images/");
#endif
  emit imagesUpdated();
}

void MainWindow::on_actionUnload_Images_triggered() {
  sfmapp->unload();
  emit imagesUpdated();
  emit imagePairsUpdated();
}
