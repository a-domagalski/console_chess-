#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "../pieces/piece.h"
#include "vector2.h"

typedef std::vector<std::vector<piece *>> pvec2d;

class board {
protected:
    unsigned short width;
    unsigned short height;
    /*
    * wektor 8x8 puste pola to puste obiekty
    * indeksy odpowiadaja pozycji na planszy
    */
    pvec2d piecesVector;

public:
    board();
    board(const board &);
    board(const pvec2d &);
    ~board();

    board &operator=(const board &);

    pvec2d getPiecesVector() const;

    void returnPieceObjectById(const char &pieceID, piece &objToReturn);

    vector2 getCoordsOfKing(const bool &) const;

    piece *getPieceByCoords(const vector2 &) const;

    piece *getKing(const bool &);

    void setCheck(const bool &, const bool &);

    void setPiecesVector(const pvec2d&);

    void initAPiece(const std::string &, const vector2 &);

    pvec2d copyPiecesVector() const;

    void deletePiecesVector(pvec2d &);

    unsigned int countPieces();

    int sumPlayerPiecesPoints(const bool&);

	friend class algInterface;

    friend class engine;

    friend class consoleChess;

    friend class moveHandler;

    friend class moveAnalyzer;
};

#endif