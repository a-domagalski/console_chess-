#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class queen : public piece {
public:
    queen();

    queen(const queen &);

    queen &operator=(const queen &);

    queen *copy() override;

    bool checkForLegalMove(const infoForPiece &) override;
};

#endif
