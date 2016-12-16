#ifndef EDGE_H
#define EDGE_H

#include "Point.h"

class Edge {

private:
	Point Point_x;
	Point Point_y;
	int e_id;

public:
	int getE_id();

	void setE_id(int e_id);

	Point getPoint_x();

	void setPoint_x(Point Point_x);

	Point getPoint_y();

	void setPoint_y(Point Point_y);
};

#endif