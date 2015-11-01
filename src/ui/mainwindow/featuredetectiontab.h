#ifndef FEATUREDETECTIONTAB_H
#define FEATUREDETECTIONTAB_H

#include <QWidget>
#include <memory>
#include <QtWidgets/qlistwidget.h>
#include "image/image.h"
#include "sfmapp.h"
#include "ui/widgets/cvimagewidget.h"

namespace Ui {
  class FeatureDetectionTab;
}

class FeatureDetectionTab : public QWidget {
Q_OBJECT

private:
  Ui::FeatureDetectionTab *ui;
  QListWidget *imagesListWidget;
  int currentImageIndex = -1;
  CVImageWidget* cvImageWidget;
  SFMApp *sfmapp;

public:
  explicit FeatureDetectionTab(QWidget *parent = 0);

  ~FeatureDetectionTab();

  void updateImages();

private:
  void updateImage();


private slots:

  void on_detectFeatures_clicked();

  void on_imagesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);


};

#endif // FEATUREDETECTIONTAB_H
