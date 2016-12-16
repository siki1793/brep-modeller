#ifndef FACES_H
#define FACES_H

#include <vector>
#include "Edges.h"

using namespace std;

class Faces {

private:
	vector<Edges> edges;
	int face_id;

public:
	vector<Edges> getEdges();

	void setEdges(vector<Edges> edges);

	int getFace_id();

	void setFace_id(int face_id);
};

#endif