#include "board.h"
#include "../pieces/pawn.h"
#include "../pieces/knight.h"
#include "../pieces/bishop.h"
#include "../pieces/rook.h"
#include "../pieces/queen.h"
#include "../pieces/king.h"

//TODO destructor with delete 
board::board() : width(8), height(8) {
    piecesVector.resize(height);

    for (unsigned short i = 0; i < height; i++) {
        piecesVector[i].resize(width);

        for (unsigned short j = 0; j < width; j++) {
            piecesVector[i][j] = new pawn();
        }
    }
}

board::board(const pvec2d &vecToCopyFrom) : width(8), height(8) {
    piecesVector = vecToCopyFrom;
}

board::~board(){}

void board::deletePiecesVector(pvec2d &vecToDelete) {
    for (unsigned short i = 0; i < height; i++) {
        for (unsigned short j = 0; j < width; j++) {
            delete vecToDelete[i][j];
        }
    }
}

pvec2d board::copyPiecesVector() const{
    pvec2d vecToReturn;
    vecToReturn.resize(piecesVector.size());
    for (unsigned short i = 0; i < piecesVector.size(); i++) {
        vecToReturn[i].resize(piecesVector[i].size());
        for (unsigned short j = 0; j < piecesVector[i].size(); j++) {
            vecToReturn[i][j] = piecesVector[i][j]->copy();
        }
    }
    return vecToReturn;
}

board::board(const board &boardToCopyFrom) {
    *this = boardToCopyFrom;
}

board &board::operator=(const board &boardToCopyFrom) {
    if (this != &boardToCopyFrom) {
        width = boardToCopyFrom.width;
        height = boardToCopyFrom.height;
        piecesVector = boardToCopyFrom.copyPiecesVector();
    } else {
        return *this;
    }
}

pvec2d board::getPiecesVector() const {
    return piecesVector;
}

void board::setCheck(const bool &isKingBlack, const bool &isChecked) {
    vector2 coords = getCoordsOfKing(isKingBlack);
    piecesVector[coords.x][coords.y]->setCheck(isChecked);
}

void board::setPiecesVector(const pvec2d& vecToSetFrom) {
    piecesVector = vecToSetFrom;
}

void board::initAPiece(const std::string &initInfo, const vector2 &coords) {
    delete piecesVector[coords.x][coords.y];
    switch (initInfo[3]) {
        case 'p':
            piecesVector[coords.x][coords.y] = new pawn();
            break;
        case 'n':
            piecesVector[coords.x][coords.y] = new knight();
            break;
        case 'b':
            piecesVector[coords.x][coords.y] = new bishop();
            break;
        case 'r':
            piecesVector[coords.x][coords.y] = new rook();
            break;
        case 'q':
            piecesVector[coords.x][coords.y] = new queen();
            break;
        case 'k':
            piecesVector[coords.x][coords.y] = new king();
            break;
        default:
            piecesVector[coords.x][coords.y] = new pawn();
            return;
    }
    if (initInfo[0] == 'B') {
        piecesVector[coords.x][coords.y]->isBlack = true;
    } else if (initInfo[0] == 'W') {
        piecesVector[coords.x][coords.y]->isBlack = false;
    }
    piecesVector[coords.x][coords.y]->position = coords;
    piecesVector[coords.x][coords.y]->isAlive = true;
}

vector2 board::getCoordsOfKing(const bool &isKingBlack) const {
    for (unsigned short i = 0; i < piecesVector.size(); i++) {
        for (unsigned short j = 0; j < piecesVector[i].size(); j++) {
            if (piecesVector[i][j]->id == 'k' && isKingBlack == piecesVector[i][j]->isBlack) {
                return vector2(i, j);
            }
        }
    }
    return vector2(-1, -1);
}

piece *board::getKing(const bool &isKingBlack) {
    vector2 coords = getCoordsOfKing(isKingBlack);
    return piecesVector[coords.x][coords.y];
}

piece *board::getPieceByCoords(const vector2 &pieceCoords) const {
    return piecesVector[pieceCoords.x][pieceCoords.y];
}

unsigned int board::countPieces() {
    unsigned int counter = 0;
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; i < height; i++) {
            if (piecesVector[i][j]->getIsAlive()) {
                counter++;
            }
        }
    }
    return counter;
}

int board::sumPlayerPiecesPoints(const bool &isPlayerBlack) {
    int pointsSum = 0;
    for (unsigned int i = 0; i < piecesVector.size(); i++) {
        for (const piece *pieceHolder: piecesVector[i]) {
            if (pieceHolder->isAlive) {
                if (pieceHolder->isBlack == isPlayerBlack) {
                    pointsSum += pieceHolder->points;
                }
            }
        }
    }
    return pointsSum;
}






