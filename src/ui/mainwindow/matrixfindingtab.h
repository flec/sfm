#ifndef MATRIXFINDINGTAB_H
#define MATRIXFINDINGTAB_H

#include <QWidget>
#include <src/sfmapp.h>

namespace Ui {
  class MatrixFindingTab;
}

class MatrixFindingTab : public QWidget {
Q_OBJECT

private:
  Ui::MatrixFindingTab *ui;
  SFMApp *sfmapp;

public:
  explicit MatrixFindingTab(QWidget *parent = 0);

  ~MatrixFindingTab();

private slots:

  void on_findInitialMatrices_clicked();

public slots:
  void updateMatches();

};

#endif // MATRIXFINDINGTAB_H
