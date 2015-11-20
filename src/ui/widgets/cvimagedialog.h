//
// Created by joschi on 20.11.15.
//

#ifndef SFM_CVIMAGEDIALOG_H
#define SFM_CVIMAGEDIALOG_H

#include <QtWidgets/qdialog.h>
#include <opencv2/core/mat.hpp>

using namespace cv;

class CVImageDialog : public QDialog {
Q_OBJECT
public:
  CVImageDialog(Mat &image);
};


#endif //SFM_CVIMAGEDIALOG_H
