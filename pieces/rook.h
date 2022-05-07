#pragma once
#include "piece.h"

class rook : public piece
{
public:
	rook();
	rook(const rook&);

	rook& operator=(const rook&);

    void setFirstMove(const bool&);
	rook* copy();
	bool checkForLegalMove(const infoForPiece& passedInfo);
};

