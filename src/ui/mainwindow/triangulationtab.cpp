#include "triangulationtab.h"
#include "ui_triangulationtab.h"

TriangulationTab::TriangulationTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TriangulationTab),
    sfmapp(SFMApp::getInstance()) {
  ui->setupUi(this);
}

TriangulationTab::~TriangulationTab() {
  delete ui;
}

void TriangulationTab::on_runInitialTriangulation_clicked() {
  sfmapp->triangulateInitialImagePair();
  updateViewer();
}

void TriangulationTab::on_runNextTriangulation_clicked() {
  sfmapp->triangulateNextImagePair();
  updateViewer();
}

void TriangulationTab::showHelp() {
  ui->qGLViewerWidget->help();
}

void TriangulationTab::updateViewer() {
  vector<shared_ptr<ImageCamera>> cameras;

  for (auto image : sfmapp->images)
    if (image->camera()->extrinsic()->data != NULL)
      cameras.push_back(image->camera());

  ui->qGLViewerWidget->update(*sfmapp->get_object_points(), cameras);
}

void TriangulationTab::on_removeLastCamera_clicked() {
  sfmapp->removeLastCamera();
  updateViewer();
}

void TriangulationTab::on_doBundleAdjustment_clicked()
{
  sfmapp->doBundleAdjustment();
  updateViewer();
}
