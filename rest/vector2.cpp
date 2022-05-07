#include "vector2.h"

vector2::vector2() : x(0), y(0) {}

vector2::vector2(const short& xCoord, const short& yCoord) :
	x(xCoord),
	y(yCoord) {}

vector2& vector2::operator=(const vector2& vectorToBeCopiedFrom) {
	if (this != &vectorToBeCopiedFrom) {
		this->x = vectorToBeCopiedFrom.x;
		this->y = vectorToBeCopiedFrom.y;
	}
	return *this;
}

bool operator==(const vector2& vectorToCheckForL, const vector2& vectorToCheckForR) {
	if (vectorToCheckForL.x == vectorToCheckForR.x && vectorToCheckForL.y == vectorToCheckForR.y) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& ostr ,const vector2& vectorToDisp) {
	ostr << vectorToDisp.x << " " << vectorToDisp.y;
	return ostr;
}