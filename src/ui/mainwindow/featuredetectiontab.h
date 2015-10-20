#ifndef FEATUREDETECTIONTAB_H
#define FEATUREDETECTIONTAB_H

#include <QWidget>
#include <memory>
#include <QtWidgets/qlistwidget.h>
#include "image/image.h"
#include "ui/widgets/cvimagewidget.h"

namespace Ui {
  class FeatureDetectionTab;
}

class FeatureDetectionTab : public QWidget {
Q_OBJECT

public:
  explicit FeatureDetectionTab(QWidget *parent = 0);

  ~FeatureDetectionTab();

public slots:

  void updateImages(vector<shared_ptr < Image>> *images);

private slots:

  void on_imagesListWidget_itemActivated(QListWidgetItem *item);

  void on_detectFeatures_clicked();

private:
  Ui::FeatureDetectionTab *ui;
  QListWidget *imagesListWidget;
  vector<shared_ptr < Image>> *images;
  CVImageWidget* cvImageWidget;
};

#endif // FEATUREDETECTIONTAB_H
