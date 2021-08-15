#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point {
public:
    Point(int x, int y);
    ~Point();

    int getX();
    void setX(int);

    int getY();
    void setY(int);

    Point& operator=(Point&);
    friend ostream& operator<< (ostream&, Point&);

    int x;
    int y;

private:
//    int x;
//    int y;

};

#endif // POINT_H
