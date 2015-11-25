#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

signals:
  void imagesUpdated();
  void imagePairsUpdated();

};

#endif // MAINWINDOW_H
