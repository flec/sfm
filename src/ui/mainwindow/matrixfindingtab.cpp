#include "matrixfindingtab.h"
#include "ui_matrixfindingtab.h"
#include "ui/uiutil.h"

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
  Mat intrinsic_matrix = UIUtil::get_mat_from_qtable(*ui->intrinsicMatrix);

  //cout << "M = "<< endl << " "  << intrinsic_matrix << endl << endl;
  cout<<"M"<<endl;
  cout<<intrinsic_matrix<<endl;
  cout<<"ME"<<endl;
  //sfmapp->findMatrices();
}

void MatrixFindingTab::updateMatches() {
  ui->matchesListWidget->clear();
  for (auto &featureMatch : sfmapp->image_pairs)
    ui->matchesListWidget->addItem(
        QString((featureMatch->image1->get_file_name() + " <-> " + featureMatch->image2->get_file_name()).c_str()));
}
