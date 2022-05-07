#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
class pawn: public piece
{
	bool performsEnPassant;

	bool basicCheckForBlack(const vector2& displacement)const;
	bool basicCheckForWhite(const vector2& displacement)const;
public:
	pawn();
	pawn(const pawn&);

	pawn& operator=(const pawn&);

	bool getPerformsEnPassant() override;
    void setPerformsEnPassant(const bool&) override;

	bool checkForLegalMove(const infoForPiece&) override;
	bool checkIfTakes(const vector2&, const piece&) const;
	bool enPassant(const infoForPiece& passedInfo);
	void setFirstMove(const bool&);	//first move - true, else - false

	
	pawn* copy() override;
};
#endif
