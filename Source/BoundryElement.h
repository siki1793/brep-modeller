#ifndef BOUNDRYELEMENT_H
#define BOUNDRYELEMENT_H

class BoundryElement {

private:
	int b_id;
	int orientation;

public:
	int getB_id();

	void setB_id(int b_id);

	int getOrientation();

	void setOrientation(int orientation);
};

#endif
