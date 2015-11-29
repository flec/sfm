#ifndef TRIANGULATIONTAB_H
#define TRIANGULATIONTAB_H

#include <QWidget>
#include <src/sfmapp.h>

namespace Ui {
  class TriangulationTab;
}

class TriangulationTab : public QWidget {
Q_OBJECT

public:
  explicit TriangulationTab(QWidget *parent = 0);

  ~TriangulationTab();

public slots:

  void on_runInitialTriangulation_clicked();

  void on_runNextTriangulation_clicked();

  void showHelp();

  void updateViewer();

private:
  Ui::TriangulationTab *ui;
  SFMApp *sfmapp;
  int i=0; // TODO: more sophisticated solution
};

#endif // TRIANGULATIONTAB_H
