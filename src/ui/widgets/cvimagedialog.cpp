// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <QtWidgets/qboxlayout.h>
#include "cvimagedialog.h"
#include "cvimagewidget.h"

CVImageDialog::CVImageDialog(Mat &image){
  CVImageWidget img_widget;
  img_widget.showImage(image);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(&img_widget);
  setLayout(mainLayout);
  this->exec();
}