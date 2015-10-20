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

public:
  explicit MainWindow(QWidget *parent = 0);

  ~MainWindow();

private slots:
  void on_actionLoad_images_triggered();


  void on_actionUnload_Images_triggered();


private:
  SFMApp *sfmapp;
  FeatureDetectionTab *featureDetectionTab;
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
