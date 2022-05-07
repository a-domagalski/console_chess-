#ifndef PLAYER_H
#define PLAYER_H

#include "../pieces/piece.h"
#include "../rest/vector2.h"
#include "../rest/board.h"

class player {
protected:
    float hasWon;
    bool isBlack;
    bool onMove;
    float points;
public:
    player();
    virtual ~player() = default;
    player(const player&);

    player& operator=(const player&);

    virtual player* clone() = 0;

    void setWinState(const float&);

    void setPoints(const float&);

    bool getIsBlack();

    float getPoints();

    float getWinState();

    float hasPlayerWon() const;

    friend class engine;

    friend class consoleChess;

};

#endif
