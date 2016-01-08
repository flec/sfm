// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <opencv2/imgproc.hpp>
#include <src/ui/widgets/cvimagedialog.h>
#include "matrixfindingtab.h"
#include "ui_matrixfindingtab.h"
#include "ui/uiutil.h"
#include "util/matrixutil.h"

MatrixFindingTab::MatrixFindingTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatrixFindingTab),
    sfmapp(SFMApp::getInstance()) {
  ui->setupUi(this);
}

MatrixFindingTab::~MatrixFindingTab() {
  delete ui;
}

void MatrixFindingTab::on_findInitialMatrices_clicked() {
  if (getCurrentImagePair() != NULL) {
    shared_ptr<ImagePair> image_pair = getCurrentImagePair();
    Mat intrinsic_matrix = UIUtil::getMatFromQtable(*ui->intrinsicMatrix);
    sfmapp->findInitialMatrices(image_pair, intrinsic_matrix);
    updateMatrices();
    emit imagePairsUpdated();
  }
}

void MatrixFindingTab::updateImagePairs() {
  ui->matchesListWidget->clear();
  for (auto &featureMatch : *sfmapp->image_pairs())
    ui->matchesListWidget->addItem(
        QString((featureMatch->image1->file_name() + " <-> " + featureMatch->image2->file_name()).c_str()));

  if (ui->matchesListWidget->count() > 0)
    ui->matchesListWidget->setCurrentRow(0);

  // display camera intrinsic matrix if available
  if (sfmapp->intrinsic_camera_parameters()->data != NULL) {
      UIUtil::insertMatInQtable(*sfmapp->intrinsic_camera_parameters(), *ui->intrinsicMatrix);
  }
}

void MatrixFindingTab::on_matchesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
  updateMatrices();
}

void MatrixFindingTab::updateMatrices() {
  shared_ptr<ImagePair> image_pair = getCurrentImagePair();

  // Update GUI
  if (image_pair != NULL) {
    Mat zeros33 = Mat::zeros(3, 3, CV_64F);
    Mat zeros31 = Mat::zeros(3, 1, CV_64F);

    if (image_pair->rotation.data != NULL) {
      Mat_<double> angles = MatrixUtil::getEulerAnglesByRotationMatrix(image_pair->rotation) / M_PI * 180;
      UIUtil::insertMatInQtable(image_pair->rotation, *ui->rotationMatrixImgPair);
      UIUtil::insertMatInQtable(angles, *ui->eulerMatrixImgPair);
    } else {
      UIUtil::insertMatInQtable(zeros33, *ui->rotationMatrixImgPair);
      UIUtil::insertMatInQtable(zeros31, *ui->eulerMatrixImgPair);
    }

    UIUtil::insertMatInQtable(
        image_pair->translation.data != NULL ? image_pair->translation : zeros31, *ui->translationMatrixImgPair);
    UIUtil::insertMatInQtable(
        image_pair->image1->camera()->projection()->data != NULL ? *image_pair->image1->camera()->projection()
                                                                 : zeros33,
        *ui->prjMatrix1);
    UIUtil::insertMatInQtable(
        image_pair->image2->camera()->projection()->data != NULL ? *image_pair->image2->camera()->projection()
                                                                 : zeros33,
        *ui->prjMatrix2);


    if (image_pair->image1->camera()->extrinsic_rotation().data != NULL) {
      Mat_<double> rot = image_pair->image1->camera()->extrinsic_rotation();
      Mat_<double> angles =
          MatrixUtil::getEulerAnglesByRotationMatrix(rot) / M_PI * 180;
      UIUtil::insertMatInQtable(rot, *ui->rotationMatrixCam1);
      UIUtil::insertMatInQtable(angles, *ui->eulerMatrixCam1);
    } else {
      UIUtil::insertMatInQtable(zeros33, *ui->rotationMatrixCam1);
      UIUtil::insertMatInQtable(zeros31, *ui->eulerMatrixCam1);
    }

    if (image_pair->image2->camera()->extrinsic_rotation().data != NULL) {
      Mat_<double> rot = image_pair->image2->camera()->extrinsic_rotation();
      Mat_<double> angles =
          MatrixUtil::getEulerAnglesByRotationMatrix(rot) / M_PI * 180;
      UIUtil::insertMatInQtable(rot, *ui->rotationMatrixCam2);
      UIUtil::insertMatInQtable(angles, *ui->eulerMatrixCam2);
    } else {
      UIUtil::insertMatInQtable(zeros33, *ui->rotationMatrixCam2);
      UIUtil::insertMatInQtable(zeros31, *ui->eulerMatrixCam2);
    }


    {
      Mat_<double> translation = image_pair->image1->camera()->extrinsic_translation();
      UIUtil::insertMatInQtable(
          translation.data != NULL ? translation
                                   : zeros31, *ui->translationMatrixCam1);
    }
    {
      Mat_<double> translation = image_pair->image2->camera()->extrinsic_translation();
      UIUtil::insertMatInQtable(
          translation.data != NULL ? translation
                                   : zeros31, *ui->translationMatrixCam2);
    }

  }
}

shared_ptr<ImagePair> MatrixFindingTab::getCurrentImagePair() {
  if (ui->matchesListWidget->currentRow() >= 0 &&
      (unsigned) ui->matchesListWidget->currentRow() < sfmapp->image_pairs()->size()) {
    return (*sfmapp->image_pairs())[ui->matchesListWidget->currentRow()];
  }
  else
    return NULL;
}
