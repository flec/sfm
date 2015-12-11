// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

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
