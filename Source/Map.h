#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include "Point.h"
#include "UV_Point.h"

using namespace std;

class Map {

private:
	string type;
	int m_id;
	string mtype;
	int space_dim;
	vector<Point> point;
	vector<UV_Point> uv_cood;
	int dimension;

public:
	UV_Point point_3d_to2D(Point point, Point pointPlan,vector<Point> axis);

	int getM_id();

	void setM_id(int m_id);

	string getType();

	void setType(string type);

	string getMtype();

	void setMtype(string mtype);

	int getSpace_dim();

	void setSpace_dim(int space_dim);

	Point getPoint(int p_id);

	void setPoints(vector<Point> points);

	UV_Point getUv_cood(int uv_id);

	void setUv_coods(vector<UV_Point> uv_cood);

	vector<Point> getPoints();

	vector<UV_Point> getUv_coods();

	int getDimension();

	void setDimension(int dimension);
};


#endif
