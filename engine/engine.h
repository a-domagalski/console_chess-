#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <array>
#include "../rest/moveHandler.h"
#include "../rest/moveAnalyzer.h"
#include "../rest/moveHandler.h"
#include "../player/player.h"
#include "../rest/board.h"

class engine {
protected:
    player *players[2];
    board chessBoard;
    moveHandler movePerformer;
    moveAnalyzer *analyzer;
    bool isBlackOnMove;
    bool hasBlackWon;
    bool hasWhiteWon;
    bool boardFlipped;
    bool autoBoardFlip;

    std::vector<std::array<vector2, 2>> moves;

    static void toggleBool(bool &); //TODO probably unnecessary (replace with std::swap)

public:

    engine();
    engine(const engine&);
    virtual ~engine();

    engine &operator=(const engine &);

    virtual engine *clone(){return this;};

    void readInitFile(const std::string &);

    virtual bool checkDestination(const vector2 &){return false;};

    virtual std::string getInput(){return "";};

    player *returnPlayerOnMove();

    virtual void chooseMode(){};

    virtual void chooseColor(){};

    void initiateHotSeat();

    void initiateAgainstComp();

    virtual void runGame();

    void setLegalMovesForPiece();

    void setAnalyzer(const vector2 &);

    void setPlayersPoints();

    virtual bool getCoords(vector2 &coordsToPass) = 0;

    virtual bool getAMove(vector2&) = 0;

    void swapPlayerOnMove();

    void executeAMove();

    void pushMoveBack(const vector2 &);

    bool isPiecePlayerOnMove(const vector2 &);

    void checkForGameEnd();

    virtual void whiteHasWon();

    virtual void blackHasWon();

    virtual void draw();

    float evalState(const player &);

    void decreaseOpponentPoints(const vector2 &);

    void get_all_legal_moves_for_player(v2vec2d&, const bool&);

    };

#endif