#include "mainwindow.h"
#include "ui_mainwindow.h"

int n = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/res/img/tsp1.png");
    int w = ui->image->width();
    int h = ui->image->height();

    ui->image->setPixmap(pix.scaled(w, h,  Qt::KeepAspectRatio));

    for (int i = 2; i <= 15; i++){
        ui->comboBox->addItem(QString::number(i));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_calculate_clicked()
{
    n = ui->comboBox->currentText().toInt();

    secondWondow = new SecondWindow(this);
    secondWondow->setN(n);
    secondWondow->show();
}
