// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef MATRIXFINDINGTAB_H
#define MATRIXFINDINGTAB_H

#include <QWidget>
#include <src/sfmapp.h>
#include <QtWidgets/qlistwidget.h>

namespace Ui {
  class MatrixFindingTab;
}

class MatrixFindingTab : public QWidget {
Q_OBJECT

private:
  Ui::MatrixFindingTab *ui;
  SFMApp *sfmapp;
  int current_image_pair_index=-1;

public:
  explicit MatrixFindingTab(QWidget *parent = 0);

  ~MatrixFindingTab();

private slots:
  void on_matchesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

public slots:

  void on_findInitialMatrices_clicked();

  void updateImagePairs();

signals:
  void imagePairsUpdated();

private:
  void updateMatrices();
  shared_ptr<ImagePair> getCurrentImagePair();

};

#endif // MATRIXFINDINGTAB_H
