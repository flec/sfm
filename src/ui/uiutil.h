// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_UIUTIL_H
#define SFM_UIUTIL_H

#include <QtWidgets/QTableWidget>
#include "opencv2/core/core.hpp"

using namespace cv;

/**
 * A generic util with static functions that helps performing UI tasks.
 */
class UIUtil {
public:
  /**
   * Convert a QTableWidget into a Mat_<double>.
   * This is ie. needed to read the camera instrinsic parameters.
   * Make sure that the Mat and the QTableWidget have the same size (cols/rows).
   *
   * table    The QTableWidget
   * returns  The cv::Mat_<double>
   */
  static Mat getMatFromQtable(QTableWidget &table);

  /**
   * Insert a matrix into a QTableWidget.
   * Make sure that the Mat and the QTableWidget have the same size (cols/rows).
   *
   * mat      The cv::Mat_<double>
   * table    The QTableWidget
   */
  static void insertMatInQtable(Mat &mat, QTableWidget &table);
};


#endif //SFM_UIUTIL_H
