#ifndef CONSOLECHESS_H
#define CONSOLECHESS_H

#include <windows.h>
#include "engine.h"

class consoleChess : public engine {
protected:
    bool isNumber(const std::string &);

    bool checkForCorrectMoveInput(const std::string &);

    void decreaseCharDigitBy1(char &);

public:

    consoleChess();
    consoleChess(const consoleChess&);
    ~consoleChess() = default;

    consoleChess &operator=(const consoleChess&);

    consoleChess * clone() override;

    std::string getInput();

    void chessToCompNotation(std::string &);

    void compTochessNotation(std::string &);

    void interpreteInput(std::string &);

    void chooseMode();

    void chooseColor();

    void displayBoardForWhite();

    void displayBoardForBlack();

    void setCursorPosition(const COORD &);

    COORD getCurrentCusrorCords();

    void displayBoard(const COORD &);

    void displayText(const std::string &);

    bool getCoords(vector2 &);

    bool strToVec2(const std::string, vector2 &);

    void displayLegalMovesForPiece();

    std::string getPieceChar(const piece *);

    bool getAMove(vector2&);

    bool checkDestination(const vector2 &);

    void runGame();

    void blackHasWon();

    void whiteHasWon();

    void draw();

    void displayPlayerPoints();

    void dispLegalPlayerMoves(const v2vec2d&);
    };

#endif

