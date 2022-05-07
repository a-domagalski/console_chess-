#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
class bishop : public piece
{
public:
	bishop();
	bishop(const bishop&);

	bishop& operator=(const bishop&);

    bishop* copy() override;
	bool checkForLegalMove(const infoForPiece&) override;
};
#endif
