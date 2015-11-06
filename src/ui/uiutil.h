//
// Created by joschi on 06.11.15.
//

#ifndef SFM_UIUTIL_H
#define SFM_UIUTIL_H

#include <QtWidgets/QTableWidget>
#include "opencv2/core/core.hpp"

using namespace cv;

class UIUtil {
public:
  static Mat get_mat_from_qtable(QTableWidget &table);
};


#endif //SFM_UIUTIL_H
