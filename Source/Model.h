#ifndef MODEL_H
#define MODEL_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include "Point.h"
#include "Face.h"
#include "UV_Point.h"
#include "Cell.h"
#include "Edges.h"
#include "Faces.h"

using namespace std;

struct K : CGAL::Exact_predicates_inexact_constructions_kernel {};

typedef CGAL::Triangulation_vertex_base_2<K>                     Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>           Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>              TDS;
typedef CGAL::Exact_predicates_tag                               Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag> CDT;
typedef CDT::Point          cdtPoint;

class Model {

private:
	string type;
	int model_id;
	vector<Cell> cells;
	vector<Edges> edges;
	vector<Faces> faces;
	set<int> connectedCellsVisited;

public:
	int getModel_id();

	void setModel_id(int model_id);

	string getType();

	void setType(string type);

	vector<Cell> getCells();

	void setCells(vector<Cell> cells);

	Cell getCell(int model_id);

	vector<Edges> getEdges();

	void setEdges(vector<Edges> edges);

	vector<Faces> getFaces();

	void setFaces(vector<Faces> faces);

	set<int> getconnectedCellsVisited();

	void setconnectedCellsVisited(int id);

	void connectedKCell(int kCell);

	void connectedStarKCell(int kCell);

	void dfcNeighbour(int kCell,int cellDim);

	void dfcStarNeighbour(int kCell,int cellDim);

	string pointContainment(Cell face,Point givenPoint);

	vector<Triangles> tessellation(Cell face);

	void writeToSTL(string stlFileName);
};

#endif
