#pragma once
#include "player.h"
class humanPlayer :
    public player
{
public:
    humanPlayer();

    humanPlayer(const humanPlayer &);

    humanPlayer &operator=(const humanPlayer &);

    humanPlayer *clone() override;
};

