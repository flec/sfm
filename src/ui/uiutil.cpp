//
// Created by joschi on 06.11.15.
//

#include <iostream>
#include "uiutil.h"

Mat UIUtil::get_mat_from_qtable(QTableWidget &table) {
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