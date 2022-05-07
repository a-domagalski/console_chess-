#include "queen.h"

queen::queen() : piece() {
    id = 'q';
    points = 90;
}

queen::queen(const queen &pieceToCopyFrom) {
    *this = pieceToCopyFrom;
}

queen &queen::operator=(const queen &pieceToCopyFrom) {
    if (this != &pieceToCopyFrom) {
        piece::operator=(pieceToCopyFrom);
    } else {
        return *this;
    }
}

queen *queen::copy() {
    return new queen(*this);
}

bool queen::checkForLegalMove(const infoForPiece &passedInfo) {
    if (((abs(passedInfo.displacement.x) == abs(passedInfo.displacement.y)) &&
         (passedInfo.displacement.x != 0 || passedInfo.displacement.y != 0)) ||
        ((passedInfo.displacement.x != 0 && passedInfo.displacement.y == 0) ||
         (passedInfo.displacement.x == 0 && passedInfo.displacement.y != 0))) {
        return true;
    } else {
        return false;
    }
}