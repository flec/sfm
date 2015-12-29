// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "cvimagewidget.h"

#ifndef CVIMAGEWIDGET_H
#define CVIMAGEWIDGET_H


CVImageWidget::CVImageWidget(QWidget *parent)
    : QWidget(parent)
{
  _tmp = cv::Mat(1,1, CV_8UC3);
  src = cv::Mat(1,1, CV_8UC3);
  refreshImage();
}

void CVImageWidget::showImage(const cv::Mat& image)
{
  // Convert the image to the RGB888 format
  switch (image.type()) {
    case CV_8UC1:
      cvtColor(image, src, CV_GRAY2RGB);
      break;
    case CV_8UC3:
      cvtColor(image, src, CV_BGR2RGB);
      break;
  }

  if(size().width() != 0 && size().height() != 0)
  {
    cv::resize(src, _tmp, cv::Size(size().width(), size().height()), 0, 0, cv::INTER_CUBIC);
    refreshImage();
  }
}

void CVImageWidget::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  painter.drawImage(QPoint(0,0), _qimage);
  painter.end();
}

void CVImageWidget::resizeEvent ( QResizeEvent * event )
{
  cv::Mat dst;
  if(event->size().width() != 0 && event->size().height() != 0)
  {
    cv::resize(src, _tmp, cv::Size(event->size().width(), event->size().height()), 0, 0, cv::INTER_CUBIC);
    refreshImage();
  }
}

void CVImageWidget::refreshImage()
{
  // QImage needs the data to be stored continuously in memory
  assert(_tmp.isContinuous());
  // Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
  // (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
  // has three bytes.
  _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);
  repaint();
}


#endif // CVIMAGEWIDGET_H
