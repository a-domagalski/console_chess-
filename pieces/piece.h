#ifndef PIECES_H
#define PIECES_H

#include <stdlib.h>
#include <vector>
#include <string>
#include <array>
#include "../rest/vector2.h"

class piece {
protected:

    bool isAlive;
    bool isBlack;
    bool piece_never_moved;
    char id;
    int points;

    vector2 position;

public:

    struct infoForPiece {

        std::vector<std::vector<piece *>> piecesVector;
        piece *destinationField;
        std::array<vector2, 2> lastMove;
        vector2 displacement;
    };

    piece();
    virtual ~piece() = default;

    piece(const piece &);


    piece &operator=(const piece &);

    friend bool operator==(const piece &, const piece &);

    bool getIsAlive() const;

    bool getIsBlack() const;

    char getID() const;

    virtual bool getPerformsEnPassant() { return false; }

    virtual bool getDoCastle() { return false; }

    virtual vector2 getPosition() const;

    virtual int getPoints();

    virtual bool isChecked() { return false; }

//	virtual bool getCheck() { return false; }
    bool isFirstMoveMade() const;

    void setPosition(const vector2 &);

    virtual void setCheck(const bool &) {}

    virtual void setDoCastle(const bool &) {}

    virtual void setPerformsEnPassant(const bool &) {}

    virtual void setFirstMove() {}

    virtual piece *copy() = 0;

    virtual bool checkForLegalMove(const infoForPiece &) = 0;

    friend class board;

    friend class moveAnalyzer;

    friend class moveHandler;

};

#endif
