#ifndef KING_H
#define KING_H
#include "piece.h"
class king : public piece
{
protected:
	//True - checked
	bool checked;
	bool doCastle;

	bool checkCastleForBlack(const infoForPiece&) const;
	bool checkCastleForWhite(const infoForPiece&) const;
public:
	king();
	king(const king&);

	king& operator=(const king&);

	bool getDoCastle() override;
    bool isChecked() override;

	void setCheck(const bool&) override;
	void setDoCastle(const bool&) override;

	king* copy() override;
	void setFirstMove(const bool&);	//first move - true, else - false
	bool checkForLegalMove(const infoForPiece&) override;
	bool checkForCastle(const infoForPiece&);
	
};
#endif
