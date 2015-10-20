#include <src/image/image.h>
#include <iostream>
#include "featuredetectiontab.h"
#include "ui_featuredetectiontab.h"

FeatureDetectionTab::FeatureDetectionTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeatureDetectionTab) {
  ui->setupUi(this);

  imagesListWidget = this->findChild<QListWidget *>("imagesListWidget");
  cvImageWidget = this->findChild<CVImageWidget *>("cvImageWidget");
}

FeatureDetectionTab::~FeatureDetectionTab() {
  delete ui;
}

void FeatureDetectionTab::updateImages(vector<shared_ptr<Image>> *images) {
  imagesListWidget->clear();
  if (images->size() > 0) {
    this->images = images;
    for (auto &image : *this->images)
      imagesListWidget->addItem(QString(image->get_file_name().c_str()));
  } else {
    this->images = NULL;
  }
}

void FeatureDetectionTab::on_imagesListWidget_itemActivated(QListWidgetItem *item) {
  int row = imagesListWidget->row(item);
  shared_ptr<Image> image = images->at(row);
  cvImageWidget->showImage(*image->get_mat_color());
}

void FeatureDetectionTab::on_detectFeatures_clicked()
{

}
