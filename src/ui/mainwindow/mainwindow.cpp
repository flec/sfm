#include <QtWidgets/qfiledialog.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionLoad_images_triggered() {
  QString images_dir = QFileDialog::getExistingDirectory(this, tr("Choose images directory"), "",
                                                         QFileDialog::ShowDirsOnly);
  sfmapp = new SFMApp(images_dir.toStdString());
}
