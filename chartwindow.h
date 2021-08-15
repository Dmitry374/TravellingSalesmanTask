#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QDialog>
#include "point.h"

namespace Ui {
class ChartWindow;
}

class ChartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow();
    void applyPoints(vector<Point> &points);

private:
    Ui::ChartWindow *ui;
};

#endif // CHARTWINDOW_H
