#ifndef FEATUREMATCHINGTAB_H
#define FEATUREMATCHINGTAB_H

#include <QWidget>
#include <QtWidgets/qlistwidget.h>
#include <ui/widgets/cvimagewidget.h>
#include <sfmapp.h>

namespace Ui {
  class FeatureMatchingTab;
}

class FeatureMatchingTab : public QWidget {
Q_OBJECT

private:
  Ui::FeatureMatchingTab *ui;
  int currentMatchIndex = -1;
  SFMApp *sfmapp;

public:
  explicit FeatureMatchingTab(QWidget *parent = 0);

  ~FeatureMatchingTab();

private slots:

  void on_matchFeatures_clicked();

  void on_matchesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
  void updateImage();

public slots:

  void updateImagePairs();

signals:

  void imagePairsUpdated();

};

#endif // FEATUREMATCHINGTAB_H
