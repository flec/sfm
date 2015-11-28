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
    Mat intrinsic_matrix = UIUtil::get_mat_from_qtable(*ui->intrinsicMatrix);
    sfmapp->findInitialMatrices(image_pair, intrinsic_matrix);
    updateMatrices();
    emit imagePairsUpdated();
  }
}

void MatrixFindingTab::updateImagePairs() {
  ui->matchesListWidget->clear();
  for (auto &featureMatch : sfmapp->image_pairs)
    ui->matchesListWidget->addItem(
        QString((featureMatch->image1->file_name() + " <-> " + featureMatch->image2->file_name()).c_str()));

  if (ui->matchesListWidget->count() > 0)
    ui->matchesListWidget->setCurrentRow(0);

  // Read the camera intrinsic matrix from disk, if available
  if (sfmapp->images.size() > 0) {
    string instrinsic_parameters_file = sfmapp->images.at(0)->file_path() + "/camera_intrinsic.yaml";
    if (FILE *file = fopen(instrinsic_parameters_file.c_str(), "r")) {
      fclose(file);
      Mat_<double> intrinsic_matrix;
      FileStorage fs(instrinsic_parameters_file, FileStorage::READ);
      fs["mat1"] >> intrinsic_matrix;
      UIUtil::insert_mat_in_qtable(intrinsic_matrix, *ui->intrinsicMatrix);
    }
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
      UIUtil::insert_mat_in_qtable(image_pair->rotation, *ui->rotationMatrixImgPair);
      UIUtil::insert_mat_in_qtable(angles, *ui->eulerMatrixImgPair);
    } else {
      UIUtil::insert_mat_in_qtable(zeros33, *ui->rotationMatrixImgPair);
      UIUtil::insert_mat_in_qtable(zeros31, *ui->eulerMatrixImgPair);
    }

    UIUtil::insert_mat_in_qtable(
        image_pair->translation.data != NULL ? image_pair->translation : zeros31, *ui->translationMatrixImgPair);
    UIUtil::insert_mat_in_qtable(
        image_pair->projection_img1.data != NULL ? image_pair->projection_img1 : zeros33, *ui->prjMatrix1);
    UIUtil::insert_mat_in_qtable(
        image_pair->projection_img2.data != NULL ? image_pair->projection_img2 : zeros33, *ui->prjMatrix2);


    if (image_pair->image1->camera()->extrinsic_rotation().data != NULL) {
      Mat_<double> rot = image_pair->image1->camera()->extrinsic_rotation();
      Mat_<double> angles =
          MatrixUtil::getEulerAnglesByRotationMatrix(rot) / M_PI * 180;
      UIUtil::insert_mat_in_qtable(rot, *ui->rotationMatrixCam1);
      UIUtil::insert_mat_in_qtable(angles, *ui->eulerMatrixCam1);
    } else {
      UIUtil::insert_mat_in_qtable(zeros33, *ui->rotationMatrixCam1);
      UIUtil::insert_mat_in_qtable(zeros31, *ui->eulerMatrixCam1);
    }

    if (image_pair->image2->camera()->extrinsic_rotation().data != NULL) {
      Mat_<double> rot = image_pair->image2->camera()->extrinsic_rotation();
      Mat_<double> angles =
          MatrixUtil::getEulerAnglesByRotationMatrix(rot) / M_PI * 180;
      UIUtil::insert_mat_in_qtable(rot, *ui->rotationMatrixCam2);
      UIUtil::insert_mat_in_qtable(angles, *ui->eulerMatrixCam2);
    } else {
      UIUtil::insert_mat_in_qtable(zeros33, *ui->rotationMatrixCam2);
      UIUtil::insert_mat_in_qtable(zeros31, *ui->eulerMatrixCam2);
    }


    {
      Mat_<double> translation = image_pair->image1->camera()->extrinsic_translation();
      UIUtil::insert_mat_in_qtable(
          translation.data != NULL ? translation
                                   : zeros31, *ui->translationMatrixCam1);
    }
    {
      Mat_<double> translation = image_pair->image2->camera()->extrinsic_translation();
      UIUtil::insert_mat_in_qtable(
          translation.data != NULL ? translation
                                   : zeros31, *ui->translationMatrixCam2);
    }

  }
}

shared_ptr<ImagePair> MatrixFindingTab::getCurrentImagePair() {
  if (ui->matchesListWidget->currentRow() >= 0 &&
      (unsigned) ui->matchesListWidget->currentRow() < sfmapp->image_pairs.size()) {
    return sfmapp->image_pairs[ui->matchesListWidget->currentRow()];
  }
  else
    return NULL;
}
