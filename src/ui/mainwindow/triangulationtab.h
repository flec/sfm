#ifndef TRIANGULATIONTAB_H
#define TRIANGULATIONTAB_H

#include <QWidget>

namespace Ui {
class TriangulationTab;
}

class TriangulationTab : public QWidget
{
    Q_OBJECT

public:
    explicit TriangulationTab(QWidget *parent = 0);
    ~TriangulationTab();

private:
    Ui::TriangulationTab *ui;
};

#endif // TRIANGULATIONTAB_H
