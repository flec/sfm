//
// Created by joschi on 20.10.15.
//

#ifndef SFM_CVIMAGEWIDGET_H
#define SFM_CVIMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <opencv2/opencv.hpp>

class CVImageWidget : public QWidget {
Q_OBJECT

public:
  explicit CVImageWidget(QWidget *parent = 0) : QWidget(parent) { }

  ~CVImageWidget(){};

  QSize sizeHint() const { return _qimage.size(); }

  QSize minimumSizeHint() const { return _qimage.size(); }

public slots:

  void showImage(const cv::Mat &image);

protected:
  void paintEvent(QPaintEvent * /*event*/);

  QImage _qimage;
  cv::Mat _tmp;
};


#endif //SFM_CVIMAGEWIDGET_H
