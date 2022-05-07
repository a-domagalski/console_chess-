#include "king.h"

king::king() : piece() {
    id = 'k';
    doCastle = false;
    points = 0;
}

king::king(const king &pieceToCopyFrom) {
    *this = pieceToCopyFrom;
}

king &king::operator=(const king &pieceToCopyFrom) {
    if (this != &pieceToCopyFrom) {
        piece::operator=(pieceToCopyFrom);
        checked = pieceToCopyFrom.checked;
        doCastle = pieceToCopyFrom.doCastle;
    } else {
        return *this;
    }
}

bool king::getDoCastle() {
    return doCastle;
}

bool king::isChecked() {
    return checked;
}

void king::setDoCastle(const bool &stateToSetFrom) {
    doCastle = stateToSetFrom;
}

king *king::copy() {
    return new king(*this);
}


//00
bool king::checkForLegalMove(const infoForPiece &passedInfo) {
    if (((abs(passedInfo.displacement.x) + abs(passedInfo.displacement.y)) == 1) ||
        (abs(passedInfo.displacement.x) == 1 && abs(passedInfo.displacement.y) == 1)) {
        return true;
    } else {
        return checkForCastle(passedInfo);
    }
}

bool king::checkCastleForBlack(const infoForPiece &passedInfo) const {
    /*
* long castle
*/
    if (passedInfo.displacement.y < 0 && !passedInfo.piecesVector[7][1]->getIsAlive()) {
        if (passedInfo.piecesVector[7][0]->isFirstMoveMade()) {
            return true;
        }
    }
        /*
        * short castle
        */
    else {
        if (passedInfo.piecesVector[7][7]->isFirstMoveMade()) {
            return true;
        }
    }
}

bool king::checkCastleForWhite(const infoForPiece &passedInfo) const {
    /*
* long castle
*/
    if (passedInfo.displacement.y < 0) {
        if (!passedInfo.piecesVector[0][1]->getIsAlive()) {
            if (passedInfo.piecesVector[0][0]->isFirstMoveMade()) {
                return true;
            }
        }
    }
        /*
        * short castle
        */
    else {
        if (!passedInfo.piecesVector[0][7]->isFirstMoveMade() &&
            !passedInfo.piecesVector[0][6]->getIsAlive()) {
            return true;
        }
    }

}

bool king::checkForCastle(const infoForPiece &passedInfo) {
    if (piece_never_moved) {
        if (passedInfo.displacement.x == 0 && abs(passedInfo.displacement.y) == 2) {
            /*
            * checking for black
            */
            if (isBlack) {
                if (checkCastleForBlack(passedInfo)) {
                    passedInfo.piecesVector[position.x][position.y]->setDoCastle(true);
                    return true;
                } else {
                    return false;
                }
            }
                /*
                * checking for white
                */
            else {
                if (checkCastleForWhite(passedInfo)) {
                    passedInfo.piecesVector[position.x][position.y]->setDoCastle(true);
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

void king::setCheck(const bool &isChecked) {
    checked = isChecked;
}

void king::setFirstMove(const bool &firstMoveToSetFrom) {
    piece_never_moved = firstMoveToSetFrom;
}
