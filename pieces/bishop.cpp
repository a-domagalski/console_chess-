#include "bishop.h"

bishop::bishop() : piece() {
    id = 'b';
    points = 30;
}

bishop::bishop(const bishop &pieceToCopyFrom) {
    *this = pieceToCopyFrom;
}

bishop &bishop::operator=(const bishop &pieceToCopyFrom) {
    if (this != &pieceToCopyFrom) {
        piece::operator=(pieceToCopyFrom);
    } else {
        return *this;
    }
}

bishop *bishop::copy() {
    return new bishop(*this);
}

bool bishop::checkForLegalMove(const infoForPiece &passedInfo) {
    if ((abs(passedInfo.displacement.x) == abs(passedInfo.displacement.y)) &&
        (passedInfo.displacement.x != 0 || passedInfo.displacement.y != 0)) {
        return true;
    } else {
        return false;
    }
}