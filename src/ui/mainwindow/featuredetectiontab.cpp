#include <src/image/image.h>
#include <iostream>
#include <sfmapp.h>
#include "featuredetectiontab.h"
#include "ui_featuredetectiontab.h"

FeatureDetectionTab::FeatureDetectionTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeatureDetectionTab),
    sfmapp(SFMApp::getInstance()) {
  ui->setupUi(this);

  imagesListWidget = this->findChild<QListWidget *>("imagesListWidget");
  cvImageWidget = this->findChild<CVImageWidget *>("cvImageWidget");
}

FeatureDetectionTab::~FeatureDetectionTab() {
  delete ui;
}

void FeatureDetectionTab::updateImages() {
  this->sfmapp = sfmapp;
  imagesListWidget->clear();
  for (auto &image : sfmapp->images)
    imagesListWidget->addItem(QString(image->get_file_name().c_str()));
}

void FeatureDetectionTab::on_detectFeatures_clicked() {
  sfmapp->detectFeatures();
  currentImageIndex = 0;
  imagesListWidget->setCurrentRow(currentImageIndex);
  updateImage();
}

void FeatureDetectionTab::updateImage() {
  if (currentImageIndex >= 0 && sfmapp->images.size() > 0) {
    shared_ptr<Image> image = sfmapp->images.at(currentImageIndex);

    if (image->get_keypoints()->size() > 0) {
      Mat picture;
      drawKeypoints(*image->get_mat_color(), *image->get_keypoints(), picture);
      cvImageWidget->showImage(picture);
    } else
      cvImageWidget->showImage(*image->get_mat_color());
  }
}

void FeatureDetectionTab::on_imagesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
  currentImageIndex = imagesListWidget->row(current);
  updateImage();
}

