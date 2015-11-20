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
  if (ui->matchesListWidget->currentRow() >= 0 && ui->matchesListWidget->currentRow() < sfmapp->image_pairs.size()) {
    Mat intrinsic_matrix = UIUtil::get_mat_from_qtable(*ui->intrinsicMatrix);

    shared_ptr<ImagePair> image_pair = sfmapp->image_pairs.at(ui->matchesListWidget->currentRow());
    sfmapp->findInitialMatrices(image_pair, intrinsic_matrix);
    UIUtil::insert_mat_in_qtable(image_pair->rotation, *ui->rotationMatrix);
    Mat_<double> angles = MatrixUtil::getEulerAnglesByRotationMatrix(image_pair->rotation) / M_PI * 180;
    UIUtil::insert_mat_in_qtable(angles, *ui->eulerMatrix);
    UIUtil::insert_mat_in_qtable(image_pair->translation, *ui->translationMatrix);
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
