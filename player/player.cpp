#include "player.h"

player::player() :
        isBlack(false),
        onMove(false),
        points(1.0),
        hasWon(0) {}

player::player(const player &playerToCpyFrom) {
    *this = playerToCpyFrom;
}

player &player::operator=(const player &playerToCpyFrom) {
    if (this != &playerToCpyFrom) {
        hasWon = playerToCpyFrom.hasWon;
        isBlack = playerToCpyFrom.isBlack;
        onMove = playerToCpyFrom.onMove;
        points = playerToCpyFrom.points;
    }
    return *this;
}


void player::setWinState(const float &winStateToGetFrom) {
    hasWon = winStateToGetFrom;
}

void player::setPoints(const float &pointsToSetFrom ){
    points = pointsToSetFrom;
}

bool player::getIsBlack() {
    return isBlack;
}

float player::getPoints(){
    return points;
}

float player::getWinState(){
    return hasWon;
}

float player::hasPlayerWon() const {
    return hasWon;
}



