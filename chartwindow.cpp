#include "chartwindow.h"
#include "ui_chartwindow.h"
#include "point.h"
#include <iostream>
#include <algorithm>
#include <QDebug>
#include <QtCharts>
#include <QBrush>

using namespace std;

ChartWindow::ChartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::applyPoints(vector<Point> &points)
{

//    qDebug() << " --- Chart Window ---";
//    for (int i = 0; i < points.size(); i++) {
//        qDebug() << points.at(i).getX() << " " << points.at(i).getY();
//    }

    QLineSeries *series = new QLineSeries();

    QString result_coordinates = "";  // координаты

    for (int i = 0; i < points.size(); i++) {
        series->append(points.at(i).getX(), points.at(i).getY());
        result_coordinates = result_coordinates + "(" + QString::number(points.at(i).getX()) + ", " + QString::number(points.at(i).getY()) + ") ";
    }
    series->append(points.at(0).getX(), points.at(0).getY());  // возврашение в исходную точку
    result_coordinates = result_coordinates + "(" + QString::number(points.at(0).getX()) + ", " + QString::number(points.at(0).getY()) + ") ";

    ui->label_coordinates->setText("Маршрут: " + result_coordinates);

    QChart *chart = new QChart();
    chart->legend()->hide();

    chart->addSeries(series);
    chart->createDefaultAxes();

    auto maxX = max_element(points.begin(), points.end(),
                                 []( const Point &a, const Point &b )
                                 {
                                     return a.x < b.x;
                                 } );

    auto maxY = max_element(points.begin(), points.end(),
                                 []( const Point &a, const Point &b )
                                 {
                                     return a.y < b.y;
                                 } );


    chart->axes(Qt::Horizontal).first()->setRange(0, maxX->getX() + 1);
    chart->axes(Qt::Vertical).first()->setRange(0, maxY->getY() + 1);

    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush());
    chart->setTitle("Оптимальный маршрут");

    QPen pen(QRgb(0x25f55c));
    pen.setWidth(5);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);

//    QChartView *chartView = new QChartView(chart);
//    chartView->resize(520, 400);
//    chartView->setRenderHint(QPainter::Antialiasing);
//    chartView->show();

    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

}

