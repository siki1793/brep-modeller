#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Map.h"
#include "Cell.h"
#include "Point.h"
#include "UV_Point.h"
#include "Faces.h"
#include "Edges.h"
#include "Edge.h"
#include "Face.h"
#include "BoundryElement.h"
#include "Model.h"
#include "Triangles.h"


using namespace std;
Model m;

int main(int argc, char *argv[]){

	Json::Value root;
	Json::Reader reader;
	const Json::Value defValue;         //used for default reference
	std::ifstream ifile(argv[1]);
	string file=argv[1];
	int pos = file.find('.'); 
	if(pos == string::npos)  
    	return 1;
		string stlFileName = file.substr(0, pos);
	cout<<file<<endl;
	// cout<<stlFileName<<endl;

	bool isJsonOK = ( ifile != NULL && reader.parse(ifile, root) );

	if(isJsonOK){

		Json::Value model = root.get("model",0);
			m.setType(model["type"].asString());
			m.setModel_id(model["id"].asInt());
			// cout<<"model type "<<m.getType()<<endl;
			// cout<<"model id "<<m.getModel_id()<<endl;
	    Json::Value cells = root.get("cells",0);
	    Json::Value maps = root.get("maps",0);
	    // cout<<"data in cells "<<cells[0].get("type","").asString()<<endl;
	    vector<Cell> c(cells.size());
		vector<Edges> e;
		vector<Faces> f;
	    cout<<"cells size "<<cells.size()<<endl;
	    for(int cellIndex=0;cellIndex<cells.size();cellIndex++)
	    {
		    	if(cells[cellIndex].isObject()){
		    		// cout<<cellIndex<<" index is an object"<<endl;
					Cell cell;
					cell.setType(cells[cellIndex].get("type","").asString());
					// cout<<"cell type "<<cell.getType()<<endl;
					cell.setC_id(cells[cellIndex].get("id","").asInt());

			    	// Json::Value cellID = cells[cellIndex].get("id","");

			    	// cout<<"cell id links to map "<<cellID<<endl;

					Json::Value boundary = cells[cellIndex]["boundary"];
					vector<BoundryElement> b;
					// cout<<"boundary index size<< ------------ "<<boundary.size()<<endl;
					for(int boundarys=0;boundarys<boundary.size();boundarys++){

					// cout<<"inner boundary index size "<<boundary[boundarys].size()<<endl;
					
					for(int boundaryIndex=0;boundaryIndex<boundary[boundarys].size();boundaryIndex++){

						BoundryElement boundaryElement;
						boundaryElement.setB_id(boundary[boundarys][boundaryIndex][0].asInt());
						// cout << "boundary index "<<boundaryIndex<<" value : " << boundaryElement.getB_id() << " , ";
						if(boundary[boundarys][boundaryIndex][1].asString()=="+")
							boundaryElement.setOrientation(1);
						else if(boundary[boundarys][boundaryIndex][1].asString() == "-")
							boundaryElement.setOrientation(0);
						// cout << boundaryElement.getOrientation() << endl;

						b.push_back(boundaryElement);

					}
					}

					cell.setBoundaryElements(b);

					// cout<<"-------------------->>>>>>>>>check if stored<<<<<<<<<------------------------"<<endl;
					// vector<BoundryElement> temp=cell.getBoundaryElements();
					// for(int i=0;i<temp.size();i++)
					// {
					// 	BoundryElement boundaryElement=temp[i];
					// 	cout << "boundary index "<<i<<" value : " << boundaryElement.getB_id() << " , ";
					// 	cout << boundaryElement.getOrientation() << endl;
					// }
					// cout<<"-------------------->>>>>>>>>xxxxxxx<<<<<<<<<------------------------"<<endl;
					Map map;
					if(maps[cell.getC_id()-1].isObject())
					{
						map.setType(maps[cell.getC_id()-1].get("type","").asString());
						// cout<<map.getType()<<endl;
						map.setM_id(maps[cell.getC_id()-1].get("id","").asInt());
						map.setMtype(maps[cell.getC_id()-1].get("mtype","").asString());
						// cout<<"----------->>dim "<<maps[cellIndex].get("dimension","").asInt()<<endl;
						map.setSpace_dim(maps[cell.getC_id()-1].get("space-dim","").asInt());
						map.setDimension(maps[cell.getC_id()-1].get("dimension","").asInt());
						cout<<"index "<<cellIndex<<" cell id "<<cell.getC_id()<<" map data "<<map.getM_id()<<"stored dimension.........."<<map.getDimension()<<endl;
						vector<Point> p;
						Json::Value points = maps[cell.getC_id()-1]["data"];
						for(int dataIndex=0;dataIndex<points.size();dataIndex++){
							Point point;
							point.setP_id(maps[cell.getC_id()-1].get("id","").asInt());
							point.setX(points[dataIndex][0].asFloat());
							point.setY(points[dataIndex][1].asFloat());
							point.setZ(points[dataIndex][2].asFloat());
							p.push_back(point);
						}
						map.setPoints(p);
						cell.setMap(map);
					}
					// cout<<" map data stored .........."<<endl;
					// Map checkMap = cell.getMap();
					// vector<Point> checkPoints  = checkMap.getPoints();
					// for(int j=0;j<checkPoints.size();j++)
					// {
					// 	Point checkPoint = checkPoints[j];
					// 	cout<<" "<<checkPoint.getX()<<" "<<checkPoint.getY()<<" "<<checkPoint.getZ()<<endl;
					// }
					c[cell.getC_id()-1]=cell;
				}
	    }
		m.setCells(c);
		cout<<"get cell size "<<m.getCells().size()<<endl;
		vector<Cell> popCells=m.getCells();
		cout<<"-------- edges --------"<<endl;
		for(int index=0;index<popCells.size();index++)
		{
			Map conMap = popCells[index].getMap();
			// cout<<"get space dim"<<conMap.getSpace_dim()<<endl;
			cout<<"index "<<index<<"cell id "<<popCells[index].getC_id()<<" get "<<popCells[index].getBoundaryElements().size()<<" ----- > map id"<<conMap.getM_id()<<" | "<<conMap.getDimension()<<endl;
			if(conMap.getDimension() == 1)
			{
				BoundryElement startBoundry = popCells[index].getBoundaryElement(0);
				BoundryElement endBoundry = popCells[index].getBoundaryElement(1);
				// cout<<"boundaryElement id "<<startBoundry.getB_id()<<" , "<<endBoundry.getB_id()<<endl;
				Point startPoint = popCells[startBoundry.getB_id()-1].getMap().getPoint(0);
				Point endPoint = popCells[endBoundry.getB_id()-1].getMap().getPoint(0);
				cout<<popCells[index].getC_id()<<" ~| "<<startPoint.getX()<<" "<<startPoint.getY()<<" "<<startPoint.getZ()<<" --------> ";
				cout<<" "<<endPoint.getX()<<" "<<endPoint.getY()<<" "<<endPoint.getZ()<<endl;
				Edge edge;
				edge.setPoint_x(startPoint);
				edge.setPoint_y(endPoint);
				edge.setE_id(popCells[index].getC_id());
				popCells[index].setCell_edges(edge);
				Edges edgs;
				edgs.setPoint_a(startPoint);
				edgs.setPoint_b(endPoint);
				edgs.setEdge_id(popCells[index].getC_id());

				e.push_back(edgs);
			}
		}
		m.setEdges(e);	//edges stored	    
		cout<<"---- face ---- "<<endl;
		for(int index=0;index<popCells.size();index++)
		{
			Map conMap = popCells[index].getMap();
			// cout<<"get space dim"<<conMap.getSpace_dim()<<endl;
			if(conMap.getDimension() == 2)
			{
				vector<BoundryElement> boundryElements = popCells[index].getBoundaryElements();
				cout<<"size here "<<boundryElements.size()<<endl;
				// cout<<"---->>"<<boundryElements[0].getB_id()<<endl;
				// cout<<"---->>"<<boundryElements[1].getB_id()<<endl;
				// cout<<"---->>"<<boundryElements[2].getB_id()<<endl;
				// cout<<"---->>"<<boundryElements[3].getB_id()<<endl;
				vector<Edge> conEdge;
				vector<Edges> conEdges;
				Face face;
				Faces faces;
				for(int boundryIndex = 0; boundryIndex < boundryElements.size();boundryIndex++)
				{	
					BoundryElement boundary = boundryElements[boundryIndex];
					cout<<"id ~| "<<boundary.getB_id()<<endl;
					Edge tempEdge = popCells[boundary.getB_id()-1].getCell_edges();


					//converting 3d points to 2d
					vector<Point> data = conMap.getPoints();
					Point planPoint = data[0];
					vector<Point> planAxis;
					planAxis.push_back(data[1]);
					planAxis.push_back(data[2]);
					UV_Point point2DX = conMap.point_3d_to2D(tempEdge.getPoint_x(),planPoint,planAxis);
					Point tempPointX = tempEdge.getPoint_x();
						  tempPointX.setUVPoint(point2DX);
						  tempEdge.setPoint_x(tempPointX);
					UV_Point point2DY = conMap.point_3d_to2D(tempEdge.getPoint_y(),planPoint,planAxis);
					Point tempPointY = tempEdge.getPoint_y();
						  tempPointY.setUVPoint(point2DY);
						  tempEdge.setPoint_y(tempPointY);
					vector<UV_Point> tempUVvector;
					tempUVvector.push_back(point2DX);
					tempUVvector.push_back(point2DY);
					// cout<<" id "<<point2DY.getUv_id()<<" ----->  "<<point2DY.getU()<<" "<<point2DY.getV()<<endl;
					conMap.setUv_coods(tempUVvector);

					Edges tempEdges ;
					tempEdges.setPoint_a(tempEdge.getPoint_x());
					tempEdges.setPoint_b(tempEdge.getPoint_y());
					tempEdges.setEdge_id(tempEdge.getE_id());
					// cout<<"---------->>>"<<tempEdges.getEdge_id()<<" x "<<tempEdge.getPoint_x().getP_id()<<" y "<<tempEdge.getPoint_y().getP_id()<<endl;					
					conEdge.push_back(tempEdge);
					conEdges.push_back(tempEdges);
				}
				face.setFace_edges(conEdge);
				face.setF_id(popCells[index].getC_id());
				faces.setEdges(conEdges);
				faces.setFace_id(popCells[index].getC_id());
				f.push_back(faces);
				popCells[index].setMap(conMap);
				popCells[index].setCell_faces(face);			
			}
		}
		m.setCells(popCells);//cell updates
		m.setFaces(f);
	}
	else
	    cout << "json not OK !!" << endl;

	cout<<"edges count "<<m.getEdges().size()<<endl;
	cout<<"faces count "<<m.getFaces().size()<<endl;
	cout<<"cell face cout"<<m.getCell(0).getCell_faces().getFace_edges().size()<<endl;
	cout<<"-------------------- 3D points ------------------------"<<endl;
	vector<Edge> fEdge = m.getCell(0).getCell_faces().getFace_edges();
	for(int i=0;i<fEdge.size();i++)
	{
		Point startPoint = fEdge[i].getPoint_x();
		Point endPoint = fEdge[i].getPoint_y();
		cout<<fEdge[i].getE_id()<<" ~| "<<startPoint.getP_id()<<" x point id "<<startPoint.getX()<<" "<<startPoint.getY()<<" "<<startPoint.getZ()<<" -------->"<<endPoint.getP_id()<<" y point id";
				cout<<" "<<endPoint.getX()<<" "<<endPoint.getY()<<" "<<endPoint.getZ()<<endl;
	}
	cout<<"--------------------- UV Points-----------------------"<<endl;
	for(int i=0;i<fEdge.size();i++)
	{
		Point startPoint = fEdge[i].getPoint_x();
		Point endPoint = fEdge[i].getPoint_y();
		cout<<fEdge[i].getE_id()<<" ~| "<<" UV point "<<startPoint.getUVPoint().getUv_id()<<" x point id "<<startPoint.getUVPoint().getU()<<" "<<startPoint.getUVPoint().getV()<<" -------->"<<endPoint.getUVPoint().getUv_id()<<" y point id";
				cout<<" "<<endPoint.getUVPoint().getU()<<" "<<endPoint.getUVPoint().getV()<<endl;
	}
	
    	

	
	while(1){
			int option;
			int kCell;
			vector<Cell> faceCells = m.getCells(); 
			cout<<"queries \n 1. Connected K-Cell \n 2. Connected Star K-Cell \n 3. Point containment \n 4. Tessellation \n 5. Exit..!!"<<endl;

			cin>>option;
			switch(option){
				case 1:
					cout<<"Give a cell "<<endl;
					cin>>kCell;
					cout<<"------------------result--------------"<<endl;
					m.connectedKCell(kCell);
					break;
				case 2:
					cout<<"Give a cell "<<endl;
					cin>>kCell;
					cout<<"------------------result--------------"<<endl;
					m.connectedStarKCell(kCell);
					break;
				case 3:
					cout<<"Give point in x y z "<<endl;
					float givenX,givenY,givenZ;
					cin>>givenX>>givenY>>givenZ;
					cout<<" "<<givenX<<" "<<givenY<<" "<<givenZ<<endl;
					Point givenPoint;
					givenPoint.setP_id(10000);
					givenPoint.setX(givenX);
					givenPoint.setY(givenY);
					givenPoint.setZ(givenZ);
					cout<<"------------------result--------------"<<endl;
					for(int fC=0;fC<m.getCells().size();fC++)
					{
						if(m.getCell(fC).getMap().getDimension()==2)
						{
							cout<<"given point is "<<m.pointContainment(m.getCell(fC),givenPoint)<<" on face with id "<<m.getCell(fC).getC_id()<<endl;
						}
					}

					break;
				case 4:
					cout<<"------------------result--------------"<<endl;
					for(int fC=0;fC<faceCells.size();fC++)
					{
						if(faceCells[fC].getMap().getDimension()==2)
						{
							Face tempFace = faceCells[fC].getCell_faces();
							tempFace.setFace_triangles(m.tessellation(m.getCell(fC)));
							faceCells[fC].setCell_faces(tempFace);
							
						}
					}
					m.setCells(faceCells);
					m.writeToSTL(stlFileName);
					break;
				default:
					exit(0);
					break;
			}
	}
	return 1;
}