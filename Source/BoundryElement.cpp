#include "BoundryElement.h"

int BoundryElement::getB_id() {
	return this->b_id;
}

void BoundryElement::setB_id(int b_id) {
	this->b_id = b_id;
}

int BoundryElement::getOrientation() {
	return this->orientation;
}

void BoundryElement::setOrientation(int orientation) {
	this->orientation = orientation;
}
