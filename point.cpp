#include "point.h"

Point::Point(int x, int y) {
    setX(x);
    setY(y);
}

Point::~Point() {
    delete &x;
    delete &y;
}

int Point::getX() {
    return x;
}

void Point::setX(int valueX) {
    x = valueX;
}

int Point::getY() {
    return y;
}

void Point::setY(int valueY) {
    y = valueY;
}

Point& Point::operator=(Point& point) {
    setX(point.getX());
    setY(point.getY());

    return *this;
}

ostream& operator<<(ostream& out, Point &point) {
    out << "(" << point.getX() << ", " << point.getY() << ")" << endl;

    return out;
}
