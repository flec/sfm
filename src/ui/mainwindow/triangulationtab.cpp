#include "triangulationtab.h"
#include "ui_triangulationtab.h"

TriangulationTab::TriangulationTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TriangulationTab)
{
    ui->setupUi(this);
}

TriangulationTab::~TriangulationTab()
{
    delete ui;
}
