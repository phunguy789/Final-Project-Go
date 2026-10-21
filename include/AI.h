#pragma once
#include "Board.h"
#include <vector>
#include <utility>
using namespace std;
class AI
{
    public:
    AI();
    pair<int,int> makemove(Board &board, int turn, int difficult);
    vector<pair<int,int>> getLegalMoves(Board &board, int turn);
    int evaluate(Board &board, int aiTurn);
    int minimax(Board &board, int depth, int turn, int aiTurn);
};