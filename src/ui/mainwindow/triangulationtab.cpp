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
  sfmapp->triangulateInitial();
  updateViewer();
}

void TriangulationTab::on_runNextTriangulation_clicked() {
  sfmapp->triangulateNext(2);
  updateViewer();
}

void TriangulationTab::showHelp() {
  ui->qGLViewerWidget->help();
}

void TriangulationTab::updateViewer() {
  vector<shared_ptr<ImageCamera>> cameras;

  for (auto image : sfmapp->images)
    if (image->camera()->rotation_translation()->data != NULL)
      cameras.push_back(image->camera());

  ui->qGLViewerWidget->update(*sfmapp->get_object_points(), cameras);
}
