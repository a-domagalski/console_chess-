#pragma once
#include "board.h"
#include "../pieces/piece.h"
#include "vector2.h"

//TODO pass piecesVector and performe
class moveHandler
{
protected:
	board* chessBoard;
	void moveAPiece(const vector2&, const vector2&);
    void deleteAPiece(const vector2&);
    void resetPiecesFlags(const vector2&);
public:
	moveHandler() {}
	moveHandler(const piece&, const piece&);
	
	void setChessBoard(board&);
	void performCastle(const vector2&, const vector2&);
	void performEnPassant(const vector2&, const vector2&);
	void executeAMove(const vector2&, const vector2&);
	void takeCastleBack(const vector2&);

	friend class engine;
	friend class consoleChess;
};

