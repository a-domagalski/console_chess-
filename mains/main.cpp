// chess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../engine/consoleChess.h"

int main()
{
    consoleChess gameInstance;
    gameInstance.readInitFile("init.txt");
    gameInstance.runGame();
}
