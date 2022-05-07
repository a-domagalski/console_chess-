#include "compPlayer.h"

compPlayer::compPlayer():player(){}

compPlayer::compPlayer(const compPlayer& playerToCpyFrom){
    *this = playerToCpyFrom;
}

compPlayer& compPlayer::operator=(const compPlayer& playerToCpyFrom){
    if (this != &playerToCpyFrom){
        player::operator=(playerToCpyFrom);
    }
    return *this;
}

compPlayer* compPlayer::clone(){
    return new compPlayer(*this);
}