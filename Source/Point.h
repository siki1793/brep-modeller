#ifndef POINT_H
#define POINT_H

#include "UV_Point.h"
#include <iostream>
#include <cmath>

using namespace std;

class Point {

private:
	float x;
	float y;
	float z;
	int p_id;
	UV_Point point2D;
	float u;
	float v;

public:
	int getP_id();

	void setP_id(int p_id);

	float getX();

	void setX(float x);

	float getY();

	void setY(float y);

	float getZ();

	void setZ(float z);

	UV_Point getUVPoint();

	void setUVPoint(UV_Point p);

	float pointU();

	float pointV();

	void setPointU(float u);

	void setPointV(float v);

	float dotProduct(Point p);

	Point diffPoint(Point p);

	Point multiPoint(Point p);

	Point addPoint(Point p);

	Point addPoints(Point a,Point b);

	float getDistPoint();

	void dividScalar(int n);

	Point crossProduct(Point p);

	int pointHig(Point p,Point o);

	bool pointOnLine(Point a,Point b);

	bool pointCounterclockwise(Point a,Point b);

	bool pointIntersection(Point a,Point b);
};

#endif
