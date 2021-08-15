#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "point.h"
#include <iostream>
#include <cstring>
#include <QDebug>

//int n = 0;

// final_path[] stores the final solution ie, the
// path of the salesman.

//int final_path[n+1];
QVector<int> final_path;

// visited[] keeps track of the already visited nodes
// in a particular path

//bool visited[n];
QVector<bool> visited;

// Stores the final minimum weight of shortest tour.
int final_res = INT_MAX;

void TSP(QVector<QVector<int>> myVector);
int firstMin(QVector<QVector<int>> adj, int i);
int secondMin(QVector<QVector<int>> adj, int i);
int secondMin(QVector<QVector<int>> adj, int i);
void TSPRec(QVector<QVector<int>> adj, int curr_bound, int curr_weight, int level, QVector<int> curr_path);
void copyToFinal(QVector<int> curr_path, int n);

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

//    ui->label->setText(QString::number(MainWindow().getN()));
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::setN(int &value)
{
    n = value;
//    ui->label->setText(QString::number(n));

    final_path.clear();
    visited.clear();
    final_res = INT_MAX;

    ui->pushButton_2->hide();

    qDebug() << "final_path.size = " << final_path.size();
    qDebug() << "visited.size = " << visited.size();

    ui->tableWidget->setRowCount(n);
    ui->tableWidget->setColumnCount(n);

    ui->tableWidget->setShowGrid(true); // Включаем сетку

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(0));
                ui->tableWidget->setItem(i, j, item);

//                ui->tableWidget->resizeRowsToContents();
//                ui->tableWidget->resizeColumnsToContents();
            }
        }
    }





//    QTableWidget *tableWidget = new QTableWidget(this);
//    tableWidget->setRowCount(n);
//    tableWidget->setColumnCount(n);

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (i == j) {
//                QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(0));
//                tableWidget->setItem(i, j, item);
//            }
//        }
//    }

//    tableWidget->show();


}

void SecondWindow::on_pushButton_clicked()
{

    QVector<QVector<int>> arr;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        QVector<int> tempVector;
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            tempVector.push_back(ui->tableWidget->item(i,j)->text().toInt());
        }
        arr.push_back(tempVector);
    }

    TSP(arr);

    ui->label_way_length->setText("Длина оптимального пути составляет: " + QString::number(final_res) + " ед.");

    ui->pushButton_2->show();

    QString result_way;
    for (int i=0; i <= arr.size(); i++) {
        if (i == arr.size()) {
            result_way = result_way + QString::number(final_path.value(i) + 1);
        } else {
            result_way = result_way + QString::number(final_path.value(i) + 1) + " -> ";
        }
    }

    ui->label_result->setText("Оптимальный (кратчайший) путь: \n" + result_way);

    qDebug() << final_res;
    qDebug() << "Path Taken : ";
    for (int i=0; i <= arr.size(); i++)
        qDebug() << final_path.value(i) + 1;
//        printf("%d ", final_path[i]+1);


//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            qDebug() << arr.value(i).value(j);
//        }
//        qDebug() << "\n";
//    }


    /* -------------------------------- */

//    QVector <QVector <int> > myVector;

//    int massive[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };

//    for(int i = 0; i < 4; i++)
//    {
//        QVector<int> tempVector;

//        for(int j = 0; j < 4; j++)
//        {
//            tempVector.push_back(massive[i][j]);
//        }
//        myVector.push_back(tempVector);
////        qDebug() << "myVector " << i << ": " << myVector.value(i);
//    }

//    /* ---------- */

//    for(int i = 0; i < 4; i++)
//    {
//        for(int j = 0; j < 4; j++)
//        {
//            qDebug() << myVector.value(i).value(j);
//        }
//        qDebug() << "\n";
//    }

    /* ---------------------------------- */

}

// This function sets up final_path[]
void TSP(QVector<QVector<int>> adj) {
//    int curr_path[N+1];
    QVector<int> curr_path;

//    qDebug() << "Size = " << n;


    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array
    int curr_bound = 0;
//    memset(curr_path, -1, n+1);
    for (int i = 0; i < adj.size() + 1; i++) {
        curr_path.push_back(-1);
    }

//    memset(visited, false, sizeof(curr_path));
    for (int i = 0; i < adj.size(); i++) {
        visited.push_back(false);
    }

    // Compute initial bound
    for (int i = 0; i < adj.size(); i++)
        curr_bound += (firstMin(adj, i) +
                       secondMin(adj, i));

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound==1)? curr_bound/2 + 1 :
                                 curr_bound/2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
//    visited[0] = true;
    visited.replace(0, true);
//    curr_path[0] = 0;
    curr_path.insert(0, 0);

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

// Function to find the minimum edge cost
// having an end at the vertex i
int firstMin(QVector<QVector<int>> adj, int i) {
    int min = INT_MAX;
    for (int k = 0; k < adj.size(); k++)
        if (adj.value(i).value(k) < min && i != k)
            min = adj.value(i).value(k);
    return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
int secondMin(QVector<QVector<int>> adj, int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < adj.size(); j++)
    {
        if (i == j)
            continue;

        if (adj.value(i).value(j) <= first)
        {
            second = first;
            first = adj.value(i).value(j);
        }
        else if (adj.value(i).value(j) <= second &&
                 adj.value(i).value(j) != first)
            second = adj.value(i).value(j);
    }
    return second;
}

// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//         space tree
// curr_path[] -> where the solution is being stored which
//                would later be copied to final_path[]
void TSPRec(QVector<QVector<int>> adj, int curr_bound, int curr_weight,
            int level, QVector<int> curr_path)
{
    // base case is when we have reached level N which
    // means we have covered all the nodes once
    if (level == adj.size())
    {
        // check if there is an edge from last vertex in
        // path back to the first vertex
        if (adj.value(curr_path.value(level-1)).value(curr_path.value(0)) != 0)
        {
            // curr_res has the total weight of the
            // solution we got
            int curr_res = curr_weight +
                    adj.value(curr_path.value(level-1)).value(curr_path.value(0));

            // Update final result and final path if
            // current result is better.
            if (curr_res < final_res)
            {
                copyToFinal(curr_path, adj.size());
                final_res = curr_res;
            }
        }
        return;
    }

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int i = 0; i < adj.size(); i++)
    {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (adj.value(curr_path.value(level-1)).value(i) != 0 &&
            visited.value(i) == false)
        {
            int temp = curr_bound;
            curr_weight += adj.value(curr_path.value(level-1)).value(i);

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level==1)
              curr_bound -= ((firstMin(adj, curr_path.value(level-1)) +
                             firstMin(adj, i))/2);
            else
              curr_bound -= ((secondMin(adj, curr_path.value(level-1)) +
                             firstMin(adj, i))/2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < final_res)
            {
//                curr_path[level] = i;
                curr_path.insert(level, i);
//                visited[i] = true;
                visited.replace(i, true);

                // call TSPRec for the next level
                TSPRec(adj, curr_bound, curr_weight, level+1,
                       curr_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
//            curr_weight -= adj[curr_path[level-1]][i];
            curr_weight -= adj.value(curr_path.value(level-1)).value(i);
            curr_bound = temp;

            // Also reset the visited array
//            memset(visited, false, sizeof(visited));
            qDebug() << "visited_1 = " << visited;
            qDebug() << "visited_size = " << visited.size();
//            visited.clear();
            for (int i = 0; i < visited.size(); i++) {
//                visited.insert(i, false);
//                visited.push_back(false);
                visited.replace(i, false);
            }
            qDebug() << "visited_2 = " << visited;

            for (int j=0; j <= level-1; j++)
                visited.replace(curr_path.value(j), true);
//                visited[curr_path[j]] = true;
        }
    }
}

// Function to copy temporary solution to
// the final solution
void copyToFinal(QVector<int> curr_path, int n)
{
    for (int i=0; i < n; i++)
        final_path.insert(i, curr_path.value(i));
    final_path.insert(n, curr_path.value(0));
}

void SecondWindow::on_pushButton_2_clicked()
{
    vector<Point> points;

//    qDebug() << "final_path = " << final_path;
//    qDebug() << "final_path.length = " << final_path.length();

    for (int i = 1; i < n+1; i++) {
        points.push_back(*new Point(final_path.value(i)+1, final_path.value(i-1)+1));
    }

//    qDebug() << "points.size = " << points.size();

    for (int i = 0; i < points.size(); i++) {
        qDebug() << points.at(i).getX() << " " << points.at(i).getY();
    }

    chartWindow = new ChartWindow(this);
    chartWindow->applyPoints(points);
    chartWindow->show();

}
