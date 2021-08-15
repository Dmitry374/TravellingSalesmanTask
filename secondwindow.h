#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include "chartwindow.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    void setN(int &n);
//    void TSP(QVector<QVector<int>> myVector);
//    int firstMin(QVector<QVector<int>> adj, int i);
//    int secondMin(QVector<QVector<int>> adj, int i);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    int n = 0;

//    // final_path[] stores the final solution ie, the
//    // path of the salesman.

//    //int final_path[n+1];
//    QVector<int> final_path;

//    // visited[] keeps track of the already visited nodes
//    // in a particular path

//    //bool visited[n];
//    QVector<bool> visited;

//    // Stores the final minimum weight of shortest tour.
//    int final_res = INT_MAX;

    Ui::SecondWindow *ui;
    ChartWindow *chartWindow;
};

#endif // SECONDWINDOW_H
