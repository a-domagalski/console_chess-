#include "rook.h"

rook::rook() :piece() {
	id = 'r';
    points = 50;
}

rook::rook(const rook& pieceToCopyFrom) {
	*this = pieceToCopyFrom;
}

rook& rook::operator=(const rook& pieceToCopyFrom) {
	if (this != &pieceToCopyFrom) {
		piece::operator=(pieceToCopyFrom);
	}
	else {
		return *this;
	}
}

rook* rook::copy() {
	return new rook(*this);
}

bool rook::checkForLegalMove(const infoForPiece& passedInfo)  {

	if ((abs(passedInfo.displacement.x) > 0 && passedInfo.displacement.y == 0) ||
		(passedInfo.displacement.x == 0 && abs(passedInfo.displacement.y) > 0)) {
		return true;
	}
	else {
		return false;
	}
}

void rook::setFirstMove(const bool& firstMoveToSetFrom) {
    piece_never_moved = firstMoveToSetFrom;
}
