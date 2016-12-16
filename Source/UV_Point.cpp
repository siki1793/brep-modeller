#include "UV_Point.h"

int UV_Point::getUv_id() {
	return this->uv_id;
}

void UV_Point::setUv_id(int uv_id) {
	this->uv_id = uv_id;
}

float UV_Point::getU() {
	return this->u;
}

void UV_Point::setU(float u) {
	this->u = u;
}

float UV_Point::getV() {
	return this->v;
}

void UV_Point::setV(float v) {
	this->v = v;
}

float UV_Point::getDist(UV_Point p){
	return sqrt(pow((this->getU()-p.getU()),2)+pow((this->getV()-p.getV()),2));
}

bool UV_Point::pointCounterclockwise(UV_Point a,UV_Point b){
	return ((b.getV()-this->getV())*(a.getU()-this->getU())) > ((a.getV()-this->getV())*(b.getU()-this->getU())) ;
}