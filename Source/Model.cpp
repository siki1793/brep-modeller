#include "Model.h"
#include "BoundryElement.h"

vector<Cell> connectedCells;
set<int> cel;

int Model::getModel_id() {
	return this->model_id;
}

void Model::setModel_id(int model_id) {
	this->model_id = model_id;
}

string Model::getType() {
	return this->type;
}

void Model::setType(string type) {
	this->type = type;
}

vector<Cell> Model::getCells() {
	// TODO - implement Model::getCells
	return this->cells;
}

void Model::setCells(vector<Cell> cells) {
	// TODO - implement Model::setCells
	this->cells = cells;
}

Cell Model::getCell(int model_id){

	return this->cells[model_id];
}

vector<Edges> Model::getEdges() {
	// TODO - implement Model::getEdges
	return this->edges;
}

void Model::setEdges(vector<Edges> edges) {
	// TODO - implement Model::setEdges
	this->edges = edges;
}

vector<Faces> Model::getFaces() {
	// TODO - implement Model::getFaces
	return this->faces;
}

void Model::setFaces(vector<Faces> faces) {
	// TODO - implement Model::setFaces
	this->faces = faces;
}

void Model::setconnectedCellsVisited(int id){
	this->connectedCellsVisited.insert(id);
}

set<int> Model::getconnectedCellsVisited(){
	return this->connectedCellsVisited;
}

void Model::dfcStarNeighbour(int kCell,int cellDim)
{
	//vector<cell> connectedCells;
	for(int cellIndex=0;cellIndex<this->getCells().size();cellIndex++)
	{
		for(int bIndex=0;bIndex<this->getCell(cellIndex).getBoundaryElements().size();bIndex++)
		{
			if(kCell == this->getCell(cellIndex).getBoundaryElement(bIndex).getB_id()){
				if(cellDim < this->getCell(cellIndex).getMap().getDimension())
					this->setconnectedCellsVisited(this->getCell(cellIndex).getC_id());
				this->dfcStarNeighbour(this->getCell(cellIndex).getC_id(),cellDim);
			}
		}
	}
}

void Model::dfcNeighbour(int kCell,int cellDim)
{
	for(int cellIndex=0;cellIndex<this->getCells().size();cellIndex++)
	{
		for(int bIndex=0;bIndex<this->getCell(cellIndex).getBoundaryElements().size();bIndex++)
		{

			if(kCell == this->getCell(cellIndex).getBoundaryElement(bIndex).getB_id()){
				cout<<"here is it--->>"<<endl;
				connectedCells.push_back(this->getCell(cellIndex));
				if((cellDim == this->getCell(cellIndex).getMap().getDimension()) && (cellDim !=0))
				{
					// cel.insert(this->getCell(cellIndex).getC_id());
					this->setconnectedCellsVisited(this->getCell(cellIndex).getC_id());
				}		
				this->dfcNeighbour(this->getCell(cellIndex).getC_id(),cellDim);
			}
		}
	}
	for(int index=0;index<connectedCells.size();index++){
		for(int bIndex=0;bIndex<connectedCells[index].getBoundaryElements().size();bIndex++){
			for(int cellIndex=0;cellIndex<cells.size();cellIndex++){
				if(connectedCells[index].getBoundaryElement(bIndex).getB_id() == cells[cellIndex].getC_id()){
					connectedCells.push_back(this->getCell(cellIndex));
					if((cellDim == this->getCell(cellIndex).getMap().getDimension()) && (cellDim !=0))
					{
						// cel.insert(this->getCell(cellIndex).getC_id());
						// cout<<"cell "<<this->getCell(cellIndex).getC_id()<<endl;
						// this->connectedCellsVisited.insert(this->getCell(cellIndex).getC_id());
						this->setconnectedCellsVisited(this->getCell(cellIndex).getC_id());
					}				
				}
			}		
		}
	}
	
}

void Model::connectedStarKCell(int kCell){
	// cout<<"k cell "<<kCell<<endl;
	// cout<<"type "<<this->getType()<<endl;
	Cell cl = this->getCell(kCell-1);
	int cellDim = cl.getMap().getDimension();
	cout<<"given cell dimension "<<cellDim<<endl;
	this->connectedCellsVisited.clear();
	this->dfcStarNeighbour(kCell,cellDim);
	cout<<"connected Start for "<<kCell<<" with higher dimensions "<<endl;
	 for(set<int>::iterator itr=this->getconnectedCellsVisited().begin();itr!=this->getconnectedCellsVisited().end();itr++)
			cout<<*itr<<endl;

}

void Model::connectedKCell(int kCell){
	cout<<"k cell "<<kCell<<endl;
	// cout<<"type "<<this->getType()<<endl;
	Cell cl = this->getCell(kCell-1);
	int cellDim = cl.getMap().getDimension();
	cout<<"given cell dimension "<<cellDim<<endl;
	this->connectedCellsVisited.clear();
	dfcNeighbour(kCell,cellDim);
	cout<<"connected cells for "<<kCell<<" with are reachable"<<endl;
	// cout<<"cell set size "<<cel.size()<<endl;
	// cout<<"cell set size "<<this->getconnectedCellsVisited().size()<<endl;
	cout<<"------------------------------------"<<endl;
	for(set<int>::iterator itr=this->connectedCellsVisited.begin();itr!=this->connectedCellsVisited.end();itr++)
		cout<<*itr<<endl;
}

string Model::pointContainment(Cell face,Point givenPoint){
	int intersectCount=0;
	Map map = face.getMap();
	vector<Point> data = map.getPoints();
	Point planPoint = data[0];
	vector<Point> planAxis;
	planAxis.push_back(data[1]);
	planAxis.push_back(data[2]);
	UV_Point givenPoint2D = map.point_3d_to2D(givenPoint,planPoint,planAxis);
	cout<<" point in 2D "<<givenPoint2D.getU()<<" "<<givenPoint2D.getV()<<endl;
	givenPoint.setUVPoint(givenPoint2D);
	vector<Edge> ed = face.getCell_faces().getFace_edges();
	
	for(int i=0;i<ed.size();i++)
	{
		Point startPoint = ed[i].getPoint_x();
		Point endPoint = ed[i].getPoint_y();
		// cout<<ed[i].getE_id()<<" ~| "<<" UV point "<<startPoint.getUVPoint().getUv_id()<<" x point id "<<startPoint.getUVPoint().getU()<<" "<<startPoint.getUVPoint().getV()<<" -------->"<<endPoint.getUVPoint().getUv_id()<<" y point id";
		// 		cout<<" "<<endPoint.getUVPoint().getU()<<" "<<endPoint.getUVPoint().getV()<<endl;
		if(givenPoint.pointOnLine(startPoint,endPoint))
		{
			return "on boundary";
		}
		else
		{
			if(givenPoint.pointIntersection(startPoint,endPoint))
			intersectCount++;
		}
	}
	if(intersectCount%2==0)
		return "outside";
	else
		return "inside";

	return "don't :-P";
}

vector<Triangles> Model::tessellation(Cell face){

	Map map = face.getMap();
	vector<Point> data = map.getPoints();
	Point planPoint = data[0];
	vector<Point> planAxis;
	planAxis.push_back(data[1]);
	planAxis.push_back(data[2]);

	Point normal = planAxis[0].crossProduct(planAxis[1]);
	cout<<"normal point x "<<normal.getX()<<" y "<<normal.getY()<<" z "<<normal.getZ()<<endl;
	normal = planPoint.multiPoint(normal);
	cout<<"normal point x "<<normal.getX()<<" y "<<normal.getY()<<" z "<<normal.getZ()<<endl;
	
	//cgal triangulation

	vector<Edge> ed = face.getCell_faces().getFace_edges();
	CDT cdt;
	for(int i=0;i<ed.size();i++)
	{
		Point startPoint = ed[i].getPoint_x();
		Point endPoint = ed[i].getPoint_y();
		// cout<<ed[i].getE_id()<<" ~| "<<" UV point "<<startPoint.getUVPoint().getUv_id()<<" x point id "<<startPoint.getUVPoint().getU()<<" "<<startPoint.getUVPoint().getV()<<" -------->"<<endPoint.getUVPoint().getUv_id()<<" y point id";
		// 		cout<<" "<<endPoint.getUVPoint().getU()<<" "<<endPoint.getUVPoint().getV()<<endl;
				cdt.insert_constraint( cdtPoint(startPoint.getUVPoint().getU(),startPoint.getUVPoint().getV()), cdtPoint(endPoint.getUVPoint().getU(),endPoint.getUVPoint().getV()));
	}
	assert(cdt.is_valid());
	vector<Triangles> triangles;
 	int count = 0;
	for (CDT::Finite_faces_iterator eit = cdt.finite_faces_begin();
		eit != cdt.finite_faces_end();
		++eit){
				cout<<" x y -----> "<<cdt.triangle(eit)[0].x()<<" "<<cdt.triangle(eit)[0].y()<<endl;
				cout<<" x y -----> "<<cdt.triangle(eit)[1].x()<<" "<<cdt.triangle(eit)[1].y()<<endl;
				cout<<" x y -----> "<<cdt.triangle(eit)[2].x()<<" "<<cdt.triangle(eit)[2].y()<<endl;
				Triangles t;
				Point p;
				UV_Point tempUV;
				tempUV.setU(cdt.triangle(eit)[0].x());
				tempUV.setV(cdt.triangle(eit)[0].y());
				p.setX(normal.getX());
				p.setY(cdt.triangle(eit)[0].x());
				p.setZ(cdt.triangle(eit)[0].y());
				p.setUVPoint(tempUV);
				t.setA(p);
				tempUV.setU(cdt.triangle(eit)[1].x());
				tempUV.setV(cdt.triangle(eit)[1].y());
				p.setX(normal.getX());
				p.setY(cdt.triangle(eit)[1].x());
				p.setZ(cdt.triangle(eit)[1].y());
				p.setUVPoint(tempUV);
				t.setB(p);
				tempUV.setU(cdt.triangle(eit)[2].x());
				tempUV.setV(cdt.triangle(eit)[2].y());
				p.setX(normal.getX());
				p.setY(cdt.triangle(eit)[2].x());
				p.setZ(cdt.triangle(eit)[2].y());
				p.setUVPoint(tempUV);
				t.setC(p);
				if(this->pointContainment(face,t.centroid())=="inside")
				{
					cout<<"triangle inserted "<<endl;
					triangles.push_back(t);
				}
				
		// if (cdt.is_constrained(*eit)) ++count;
		}
		// Face tempFace = face.getCell_faces();
		// tempFace.setFace_triangles(triangles);
		// face.setCell_faces(tempFace);

		
		cout<<"cell id "<<face.getC_id()<<endl;

	// cout << "The number of resulting constrained edges is  ";
	// cout <<  count << std::endl;

	return triangles;
}

void Model::writeToSTL(string stlFileName){
	//writing to stl file
	stlFileName = "stlfile/"+stlFileName+".stl";
	
	vector<Cell> fCs = this->getCells();
	for(int fC=0;fC<fCs.size();fC++)
			{
				if(fCs[fC].getMap().getDimension()==2)
				{
					vector<Triangles> triangles=fCs[fC].getCell_faces().getFace_triangles();
					ofstream stlFile;
					stlFile.open(stlFileName.c_str());
					stlFile <<"solid plane"<<endl;
					for(int i=0;i<triangles.size();i++){
						Point normal = triangles[i].normalOfTriangle();
						stlFile << "\tfacet normal "<<normal.getX()<<" "<<normal.getY()<<" "<<normal.getZ()<<endl;
						stlFile << "\t\touter loop"<<endl;
						stlFile << "\t\t\tvertex "<<triangles[i].getA().getX()<<" "<<triangles[i].getA().getY()<<" "<<triangles[i].getA().getZ()<<endl;
						stlFile << "\t\t\tvertex "<<triangles[i].getB().getX()<<" "<<triangles[i].getB().getY()<<" "<<triangles[i].getB().getZ()<<endl;
						stlFile << "\t\t\tvertex "<<triangles[i].getC().getX()<<" "<<triangles[i].getC().getY()<<" "<<triangles[i].getC().getZ()<<endl;
						stlFile << "\t\tendloop"<<endl;
						stlFile << "\tendfacet"<<endl;
					}
					stlFile <<"endsolid"<<endl;
					stlFile.close();
				}
			}
	cout<<"check stl file at "<<stlFileName<<endl;
}