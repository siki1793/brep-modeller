#ifndef FACE_H
#define FACE_H

#include "Edge.h"
#include <vector>
#include "Triangles.h"

using namespace std;

class Face {

private:
	vector<Edge> face_edges;
	vector<Triangles> face_triangles;
	int f_id;

public:
	int getF_id();

	void setF_id(int f_id);

	vector<Edge> getFace_edges();

	void setFace_edges(vector<Edge> face_edges);

	Edge getFace_edge(int e_id);

	vector<Triangles> getFace_triangles();

	void setFace_triangles(vector<Triangles> face_triangles);

	Triangles getFace_triangle(int id);
};

#endif