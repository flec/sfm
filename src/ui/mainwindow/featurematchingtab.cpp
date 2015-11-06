#include "featurematchingtab.h"
#include "ui_featurematchingtab.h"

FeatureMatchingTab::FeatureMatchingTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeatureMatchingTab),
    sfmapp(SFMApp::getInstance()) {
  ui->setupUi(this);
}

FeatureMatchingTab::~FeatureMatchingTab() {
  delete ui;
}

void FeatureMatchingTab::updateMatches() {
  ui->matchesListWidget->clear();
  for (auto &featureMatch : sfmapp->image_pairs)
    ui->matchesListWidget->addItem(
        QString((featureMatch->image1->get_file_name() + " <-> " + featureMatch->image2->get_file_name()).c_str()));
  emit matchesUpdated();
}

void FeatureMatchingTab::updateImage() {
  if (currentMatchIndex >= 0 && sfmapp->images.size() > 0) {
    shared_ptr<ImagePair> matches = sfmapp->image_pairs.at(currentMatchIndex);
    shared_ptr<Image> image1 = matches->image1;
    shared_ptr<Image> image2 = matches->image2;

    if (matches->matches.size() > 0) {
      Mat picture;
      drawMatches(*image1->get_mat_color(), *image1->get_keypoints(), *image2->get_mat_color(),
                  *image2->get_keypoints(), matches->matches, picture);
      ui->cvImageWidget->showImage(picture);
    } else
      ui->cvImageWidget->showImage(*image1->get_mat_grey());
  }
}


void FeatureMatchingTab::on_matchFeatures_clicked() {
  sfmapp->matchFeatures();
  updateMatches();
  currentMatchIndex = 0;
  ui->matchesListWidget->setCurrentRow(currentMatchIndex);
  updateImage();
}

void FeatureMatchingTab::on_matchesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
  currentMatchIndex = ui->matchesListWidget->row(current);
  updateImage();
}
