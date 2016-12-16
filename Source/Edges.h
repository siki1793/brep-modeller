#ifndef EDGES_H
#define EDGES_H

#include "Point.h"

class Edges {

private:
	int edge_id;
	Point Point_a;
	Point Point_b;

public:
	int getEdge_id();

	void setEdge_id(int edge_id);

	Point getPoint_a();

	void setPoint_a(Point Point_a);

	Point getPoint_b();

	void setPoint_b(Point Point_b);
};

#endif