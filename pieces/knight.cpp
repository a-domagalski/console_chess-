#include "knight.h"

knight::knight() : piece() {
    id = 'n';
    points = 30;
}

knight::knight(const knight &pieceToCopyFrom) {
    *this = pieceToCopyFrom;
}

knight &knight::operator=(const knight &pieceToCopyFrom) {
    if (this != &pieceToCopyFrom) {
        piece::operator=(pieceToCopyFrom);
    } else {
        return *this;
    }
}

knight *knight::copy() {
    return new knight(*this);
}

bool knight::checkForLegalMove(const infoForPiece &passedInfo) {
    unsigned short displacementY = abs(passedInfo.displacement.y);
    unsigned short displacementX = abs(passedInfo.displacement.x);
    if ((displacementX == 1 && displacementY == 2) || (displacementX == 2 && displacementY == 1)) {
        return true;
    } else {
        return false;
    }
}
