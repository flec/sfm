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

private slots:

  void on_runTriangulation_clicked();

private:
  Ui::TriangulationTab *ui;
  SFMApp *sfmapp;
};

#endif // TRIANGULATIONTAB_H
