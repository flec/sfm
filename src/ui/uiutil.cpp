// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iostream>
#include "uiutil.h"

Mat UIUtil::getMatFromQtable(QTableWidget &table) {
  Mat_<double> mat(table.rowCount(), table.columnCount());
  for (int row = 0; row < table.rowCount(); row++) {
    for (int col = 0; col < table.columnCount(); col++) {
      if (table.item(row, col) != NULL)
        mat(row, col) = table.item(row, col)->text().toDouble();
      else
        mat(row, col) = 0;
    }
  }
  return mat;
}


void UIUtil::insertMatInQtable(Mat &mat, QTableWidget &table) {
  for (int row = 0; row < mat.size().height; row++) {
    for (int col = 0; col < mat.size().width; col++) {
      if (table.item(row, col) == 0)
        table.setItem(row, col, new QTableWidgetItem());
      table.item(row, col)->setText(QString::number(mat.at<double>(row, col), 'g', 15));
    }
  }
}