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

  void on_matchesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

public slots:

  void on_matchFeatures_clicked();

  void updateImagePairs();

  void updateImage();

signals:

  void imagePairsUpdated();

};

#endif // FEATUREMATCHINGTAB_H
