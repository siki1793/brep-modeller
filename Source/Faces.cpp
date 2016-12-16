#include "Faces.h"

vector<Edges> Faces::getEdges() {
	// TODO - implement Faces::getEdges
	return this->edges;
}

void Faces::setEdges(vector<Edges> edges) {
	// TODO - implement Faces::setEdges
	this->edges = edges;
}

int Faces::getFace_id() {
	return this->face_id;
}

void Faces::setFace_id(int face_id) {
	this->face_id = face_id;
}
