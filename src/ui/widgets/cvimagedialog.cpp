//
// Created by joschi on 20.11.15.
//

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