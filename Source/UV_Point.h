#ifndef UV_POINT_H
#define UV_POINT_H

#include <cmath>

class UV_Point {

private:
	float u;
	float v;
	int uv_id;

public:
	int getUv_id();

	void setUv_id(int uv_id);

	float getU();

	void setU(float u);

	float getV();

	void setV(float v);

	float getDist(UV_Point p);

	bool pointCounterclockwise(UV_Point a,UV_Point b);
};

#endif
