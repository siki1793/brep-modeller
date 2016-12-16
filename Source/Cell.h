#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
#include "BoundryElement.h"
#include "Map.h"
#include "Face.h"
#include "Edge.h"

using namespace std;

class Cell {

private:
	string type;
	int c_id;
	Map map;
	vector<BoundryElement> boundaryElement;
	Face cell_faces;
	Edge cell_edges;

public:
	int getC_id();

	void setC_id(int c_id);

	string getType();

	void setType(string type);

	Map getMap();

	void setMap(Map map);

	vector<BoundryElement> getBoundaryElements();

	void setBoundaryElements(vector<BoundryElement> boundaryElement);

	Face getCell_faces();

	void setCell_faces(Face cell_faces);

	Edge getCell_edges();

	void setCell_edges(Edge cell_edges);

	BoundryElement getBoundaryElement(int b_id);
};

#endif
