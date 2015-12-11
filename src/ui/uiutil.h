// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef SFM_UIUTIL_H
#define SFM_UIUTIL_H

#include <QtWidgets/QTableWidget>
#include "opencv2/core/core.hpp"

using namespace cv;

class UIUtil {
public:
  static Mat get_mat_from_qtable(QTableWidget &table);
  static void insert_mat_in_qtable(Mat &mat, QTableWidget &table);
};


#endif //SFM_UIUTIL_H
