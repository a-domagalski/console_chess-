#include "humanPlayer.h"

humanPlayer::humanPlayer():player(){}

humanPlayer::humanPlayer(const humanPlayer& playerToCpyFrom){
    *this = playerToCpyFrom;
}

humanPlayer& humanPlayer::operator=(const humanPlayer& playerToCpyFrom){
    if (this != &playerToCpyFrom){
        player::operator=(playerToCpyFrom);
    }
    return *this;
}

humanPlayer* humanPlayer::clone(){
    return new humanPlayer(*this);
}