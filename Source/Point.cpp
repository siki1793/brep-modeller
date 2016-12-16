#include "Point.h"

int Point::getP_id() {
	return this->p_id;
}

void Point::setP_id(int p_id) {
	this->p_id = p_id;
}

float Point::getX() {
	return this->x;
}

void Point::setX(float x) {
	this->x = x;
}

float Point::getY() {
	return this->y;
}

void Point::setY(float y) {
	this->y = y;
}

float Point::getZ() {
	return this->z;
}

void Point::setZ(float z) {
	this->z = z;
}

UV_Point Point::getUVPoint(){
	// cout<<"get point id "<<this->point2D.getUv_id()<<" ----->  "<<this->point2D.getU()<<" "<<this->point2D.getV()<<endl;	
	return this->point2D;
}

void Point::setUVPoint(UV_Point p){
	// cout<<"-------- inside point -----------"<<endl;
	// cout<<" id "<<p.getUv_id()<<" ----->  "<<p.getU()<<" "<<p.getV()<<endl;
	this->point2D = p;
	// cout<<" id "<<this->point2D.getUv_id()<<" ----->  "<<this->point2D.getU()<<" "<<this->point2D.getV()<<endl;
	// cout<<"-------- outgoing point --------- "<<endl;
}

void Point::setPointU(float u){
	this->u=u;
}

void Point::setPointV(float v){
	this->v=v;
}

float Point::dotProduct(Point p){
	return this->getX()*p.getX()+this->getY()*p.getY()+this->getZ()*p.getZ();
}

Point Point::diffPoint(Point p){
	p.setX(this->getX()-p.getX());
	p.setY(this->getY()-p.getY());
	p.setZ(this->getZ()-p.getZ());
	return p;
}

Point Point::multiPoint(Point p){
	p.setX(this->getX()*p.getX());
	p.setY(this->getY()*p.getY());
	p.setZ(this->getZ()*p.getZ());
	return p;
}

Point Point::addPoint(Point p){
	p.setX(this->getX()+p.getX());
	p.setY(this->getY()+p.getY());
	p.setZ(this->getZ()+p.getZ());
	return p;
}

float Point::getDistPoint(){
	return sqrt(pow((this->getX()),2)+pow((this->getY()),2)+pow((this->getZ()),2));
}

Point Point::addPoints(Point a,Point b){
	a.setX(this->getX()+a.getX()+b.getX());
	a.setY(this->getY()+a.getY()+b.getY());
	a.setZ(this->getZ()+a.getZ()+b.getZ());
	return a;
}

void Point::dividScalar(int n){
	this->setX(this->getX()/n);
	this->setY(this->getY()/n);
	this->setZ(this->getZ()/n);
}

int Point::pointHig(Point p,Point o){
	o=o.multiPoint(p);
	return (abs(o.getX()+o.getY()+o.getZ())/p.getDistPoint());
}

Point Point::crossProduct(Point p){
	Point result;
	result.setX((this->getY()*p.getZ())-(this->getZ()*p.getY()));
	result.setY((this->getZ()*p.getX())-(this->getX()*p.getZ()));
	result.setZ((this->getX()*p.getY())-(this->getY()*p.getX()));
	return result;
}

bool Point::pointOnLine(Point a,Point b){
		return this->getUVPoint().getDist(a.getUVPoint())+this->getUVPoint().getDist(b.getUVPoint()) == a.getUVPoint().getDist(b.getUVPoint());
	}
	

bool Point::pointIntersection(Point a,Point b){
	UV_Point pointAtInf;
	pointAtInf.setU(10000);
	pointAtInf.setV(10000);

	return this->getUVPoint().pointCounterclockwise(a.getUVPoint(),b.getUVPoint()) != pointAtInf.pointCounterclockwise(a.getUVPoint(),b.getUVPoint()) && this->getUVPoint().pointCounterclockwise(pointAtInf,a.getUVPoint()) != this->getUVPoint().pointCounterclockwise(pointAtInf,b.getUVPoint()) ; 

}
