all:
	g++ Source/main.cpp Source/BoundryElement.cpp Source/Cell.cpp Source/Edge.cpp Source/Face.cpp Source/Triangles.cpp Source/Edges.cpp Source/Faces.cpp Source/Map.cpp Source/Model.cpp Source/Point.cpp Source/UV_Point.cpp -g -o output -ljsoncpp -lCGAL -lgmp