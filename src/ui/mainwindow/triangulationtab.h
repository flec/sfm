// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef TRIANGULATIONTAB_H
#define TRIANGULATIONTAB_H

#include <QWidget>
#include "sfmapp.h"

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

private slots:
  void on_removeLastCamera_clicked();

  void on_doBundleAdjustment_clicked();

  void on_centerPivot_clicked();

  void on_denseReconstruct_clicked();

private:
  Ui::TriangulationTab *ui;
  SFMApp *sfmapp;
};

#endif // TRIANGULATIONTAB_H
