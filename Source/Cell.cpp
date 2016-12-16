#include "Cell.h"

int Cell::getC_id() {
	return this->c_id;
}

void Cell::setC_id(int c_id) {
	this->c_id = c_id;
}

string Cell::getType() {
	return this->type;
}

void Cell::setType(string type) {
	this->type = type;
}

Map Cell::getMap() {
	return this->map;
}

void Cell::setMap(Map map) {
	this->map = map;
}

vector<BoundryElement> Cell::getBoundaryElements() {
	// TODO - implement Cell::getBoundaryElement
	return this->boundaryElement;
}

void Cell::setBoundaryElements(vector<BoundryElement> boundaryElement) {
	// TODO - implement Cell::setBoundaryElement
	this->boundaryElement = boundaryElement;
}

Face Cell::getCell_faces() {
	return this->cell_faces;
}

void Cell::setCell_faces(Face cell_faces) {
	this->cell_faces = cell_faces;
}

Edge Cell::getCell_edges() {
	return this->cell_edges;
}

void Cell::setCell_edges(Edge cell_edges) {
	this->cell_edges = cell_edges;
}

BoundryElement Cell::getBoundaryElement(int b_id){
	return this->boundaryElement[b_id];
}
