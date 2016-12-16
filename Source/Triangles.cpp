#include "Triangles.h"

void Triangles::setA(Point a){
    this->a=a;
}

void Triangles::setB(Point b){
    this->b=b;
}

void Triangles::setC(Point c){
    this->c=c;
}

Point Triangles::getA(){
    return this->a;
}

Point Triangles::getB(){
    return this->b;
}
        
Point Triangles::getC(){
    return this->c;
}

Point Triangles::normalOfTriangle(){
    Point u = this->b.diffPoint(this->a);
    Point v = this->c.diffPoint(this->a);
    return u.crossProduct(v);
}

Point Triangles::centroid(){
    Point temp = this->a.addPoints(this->b,this->c);
    
    temp.dividScalar(3);
    
    return temp;
}
