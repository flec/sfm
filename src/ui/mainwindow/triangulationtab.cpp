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
}

void TriangulationTab::on_runNextTriangulation_clicked() {
  sfmapp->triangulateNext(1);
}

void TriangulationTab::showHelp() {
  ui->qGLViewerWidget->help();
}
