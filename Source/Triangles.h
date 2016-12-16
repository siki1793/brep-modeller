#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "Point.h"
#include "UV_Point.h"

class Triangles{
    private:
        Point a;
        Point b;
        Point c;

    public:
        void setA(Point a);

        void setB(Point b);

        void setC(Point c);

        Point getA();

        Point getB();

        Point getC();

        Point normalOfTriangle();

        Point centroid();
};




#endif