#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
class knight : public piece
{
public:
	knight();
	knight(const knight&);

	knight& operator=(const knight&);

    knight* copy();
	bool checkForLegalMove(const infoForPiece&);

};
#endif
