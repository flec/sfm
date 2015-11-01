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
  SFMApp *sfmapp;
  FeatureDetectionTab *featureDetectionTab;
  FeatureDetectionTab *featureMatchingTab;
  Ui::MainWindow *ui;

public:
  explicit MainWindow(QWidget *parent = 0);

  ~MainWindow();

private slots:
  void on_actionLoad_images_triggered();


  void on_actionUnload_Images_triggered();

};

#endif // MAINWINDOW_H
