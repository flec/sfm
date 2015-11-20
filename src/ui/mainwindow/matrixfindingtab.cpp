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
  if (ui->matchesListWidget->currentRow() >= 0 &&
      (unsigned) ui->matchesListWidget->currentRow() < sfmapp->image_pairs.size()) {
    Mat intrinsic_matrix = UIUtil::get_mat_from_qtable(*ui->intrinsicMatrix);

    shared_ptr<ImagePair> image_pair = sfmapp->image_pairs.at(ui->matchesListWidget->currentRow());
    sfmapp->findInitialMatrices(image_pair, intrinsic_matrix);

    // Update GUI
    Mat_<double> angles = MatrixUtil::getEulerAnglesByRotationMatrix(image_pair->rotation) / M_PI * 180;
    UIUtil::insert_mat_in_qtable(image_pair->rotation, *ui->rotationMatrix);
    UIUtil::insert_mat_in_qtable(angles, *ui->eulerMatrix);
    UIUtil::insert_mat_in_qtable(image_pair->translation, *ui->translationMatrix);
    UIUtil::insert_mat_in_qtable(image_pair->projection_img1, *ui->prjMatrix1);
    UIUtil::insert_mat_in_qtable(image_pair->projection_img2, *ui->prjMatrix2);

    //showRectifiedImage(image_pair);
  }
}

void MatrixFindingTab::updateImagePairs() {
  ui->matchesListWidget->clear();
  for (auto &featureMatch : sfmapp->image_pairs)
    ui->matchesListWidget->addItem(
        QString((featureMatch->image1->get_file_name() + " <-> " + featureMatch->image2->get_file_name()).c_str()));

  if (ui->matchesListWidget->count() > 0)
    ui->matchesListWidget->setCurrentRow(0);

  if (sfmapp->images.size() > 0) {
    string instrinsic_parameters_file = sfmapp->images.at(0)->get_file_path() + "/camera_intrinsic.yaml";
    if (FILE *file = fopen(instrinsic_parameters_file.c_str(), "r")) {
      fclose(file);
      Mat_<double> intrinsic_matrix;
      FileStorage fs(instrinsic_parameters_file, FileStorage::READ);
      fs["mat1"] >> intrinsic_matrix;
      UIUtil::insert_mat_in_qtable(intrinsic_matrix, *ui->intrinsicMatrix);
    }

  }
}

void MatrixFindingTab::showRectifiedImage(shared_ptr<ImagePair> &image_pair) {
  Mat D1 = Mat::zeros(1, 4, CV_64F);
  Mat D2 = Mat::zeros(1, 4, CV_64F);
  Mat map1x, map1y, map2x, map2y;
  Mat imgU1, imgU2;
  initUndistortRectifyMap(*sfmapp->intrinsic_camera_parameters(), D1, image_pair->rotation_rect_img1,
                          image_pair->projection_img1, image_pair->image1->get_mat_grey()->size(), CV_32FC1, map1x,
                          map1y);
  initUndistortRectifyMap(*sfmapp->intrinsic_camera_parameters(), D2, image_pair->rotation_rect_img2,
                          image_pair->projection_img2, image_pair->image2->get_mat_grey()->size(), CV_32FC1, map2x,
                          map2y);

  remap(*image_pair->image1->get_mat_color(), imgU1, map1x, map1y, INTER_LINEAR, BORDER_CONSTANT, Scalar());
  remap(*image_pair->image2->get_mat_color(), imgU2, map2x, map2y, INTER_LINEAR, BORDER_CONSTANT, Scalar());

  CVImageDialog img_dlg(imgU1);
  CVImageDialog img_dlg2(imgU2);
}
