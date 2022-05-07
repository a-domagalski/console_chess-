#pragma once

#include "player.h"

class compPlayer :
        public player {
public:
    compPlayer();

    compPlayer(const compPlayer &);

    compPlayer &operator=(const compPlayer &);

    compPlayer *clone() override;
};

