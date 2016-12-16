#include "Map.h"

UV_Point Map::point_3d_to2D(Point point, Point pointPlan,vector<Point> axis) {
	// TODO - implement Map::point_3d_to2D
	UV_Point tempUV;
	point.diffPoint(pointPlan);
	tempUV.setU(point.dotProduct(axis[0]));
	tempUV.setV(point.dotProduct(axis[1]));
	tempUV.setUv_id(point.getP_id());

	// cout<<"++++++++++======="<<tempUV.getUv_id()<<" U "<<tempUV.getU()<<" V "<<tempUV.getV()<<endl;

	return tempUV;
}

int Map::getM_id() {
	return this->m_id;
}

void Map::setM_id(int m_id) {
	this->m_id = m_id;
}

string Map::getType() {
	return this->type;
}

void Map::setType(string type) {
	this->type = type;
}

string Map::getMtype() {
	return this->mtype;
}

void Map::setMtype(string mtype) {
	this->mtype = mtype;
}

int Map::getSpace_dim() {
	return this->space_dim;
}

void Map::setSpace_dim(int space_dim) {
	this->space_dim = space_dim;
}

Point Map::getPoint(int p_id) {
	return this->point[p_id];
}

void Map::setPoints(vector<Point> point) {
	this->point = point;
}

UV_Point Map::getUv_cood(int uv_id) {
	return this->uv_cood[uv_id];
}

void Map::setUv_coods(vector<UV_Point> uv_cood) {
	this->uv_cood = uv_cood;
}

vector<Point> Map::getPoints(){
	return this->point;
}

vector<UV_Point> Map::getUv_coods(){
	return this->uv_cood;
}

int Map::getDimension() {
	return this->dimension;
}

void Map::setDimension(int dimension) {
	this->dimension = dimension;
}
