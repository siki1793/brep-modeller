#include "Face.h"

int Face::getF_id() {
	return this->f_id;
}

void Face::setF_id(int f_id) {
	this->f_id = f_id;
}

vector<Edge> Face::getFace_edges() {
	// TODO - implement Faces::getFace_edges
	return this->face_edges;
}

void Face::setFace_edges(vector<Edge> face_edges) {
	// TODO - implement Faces::setFace_edges
	this->face_edges = face_edges;
}

Edge Face::getFace_edge(int e_id){
	return this->face_edges[e_id];
}

vector<Triangles> Face::getFace_triangles(){
	return this->face_triangles;
}

void Face::setFace_triangles(vector<Triangles> face_triangles){
	this->face_triangles = face_triangles;
}

Triangles Face::getFace_triangle(int id){
	return this->face_triangles[id];
}