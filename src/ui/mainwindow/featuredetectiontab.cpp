// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <src/image/image.h>
#include <sfmapp.h>
#include <src/ui/widgets/cvimagedialog.h>
#include "featuredetectiontab.h"
#include "ui_featuredetectiontab.h"

FeatureDetectionTab::FeatureDetectionTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeatureDetectionTab),
    sfmapp(SFMApp::getInstance()) {

  ui->setupUi(this);
}

FeatureDetectionTab::~FeatureDetectionTab() {
  delete ui;
}

void FeatureDetectionTab::updateImages() {
  ui->imagesListWidget->clear();
  for (auto &image : *sfmapp->images())
    ui->imagesListWidget->addItem(QString(image->file_name().c_str()));
}

void FeatureDetectionTab::on_detectFeatures_clicked() {
  sfmapp->detectFeatures();
  currentImageIndex = 0;
  ui->imagesListWidget->setCurrentRow(currentImageIndex);
  updateImage();
}

void FeatureDetectionTab::updateImage() {

  if (currentImageIndex >= 0 && sfmapp->images()->size() > 0) {
    shared_ptr<Image> image = sfmapp->images()->at(currentImageIndex);

    if (image->keypoints()->size() > 0) {
      Mat picture;
      drawKeypoints(*image->mat_color(), *image->keypoints(), picture);
      ui->cvImageWidget->showImage(picture);
    } else
      ui->cvImageWidget->showImage(*image->mat_color());
  }
}

void FeatureDetectionTab::on_imagesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
  currentImageIndex = ui->imagesListWidget->row(current);
  updateImage();
}
