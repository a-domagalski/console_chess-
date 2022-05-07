cmake_minimum_required(VERSION 3.20)
project(chess_clion_)

set(CMAKE_CXX_STANDARD 14)

file(GLOB chess_clion__SRC
        "*.h"
        "*.cpp"
        )
set(glob
        pieces/bishop.h pieces/bishop.cpp
        rest/board.h rest/board.cpp
        player/compPlayer.h player/compPlayer.cpp
        engine/consoleChess.h engine/consoleChess.cpp
        engine/engine.h engine/engine.cpp
        player/humanPlayer.h player/humanPlayer.cpp
        pieces/king.h pieces/king.cpp
        pieces/knight.h pieces/knight.cpp
        rest/moveAnalyzer.h rest/moveAnalyzer.cpp
        rest/moveHandler.h rest/moveHandler.cpp
        pieces/pawn.h pieces/pawn.cpp
        pieces/piece.h pieces/piece.cpp
        player/player.h player/player.cpp
        pieces/queen.h pieces/queen.cpp
        pieces/rook.h pieces/rook.cpp
        rest/vector2.h rest/vector2.cpp)

add_executable(chess_clion mains/main.cpp
        ${glob} )
