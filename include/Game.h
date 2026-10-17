#pragma once
#include <Board.h>
#include <AI.h>
class Game
{
    public:
    Board board;
    AI ai;
    int turn, winner;
    int cntwhite, cntblack;
    int mode, difficult;
    bool gameover;
    Game();
    void reset();
    void playmove(int i, int j);
}