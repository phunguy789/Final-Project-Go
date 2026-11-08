#pragma once
#include "Board.h"
#include <vector>
#include <utility>
using namespace std;
class AI
{
    public:
    AI();
    pii makemove(Board &board, int turn, int difficult);
    vector<pii> getLegalMoves(Board &board);
    int evaluate(Board &board, int aiTurn);
    int minimax(Board &board, int depth, int turn, int aiTurn);
    pii findBestMove(Board& board, int depth, int aiTurn);
    vector<pii> getCandidateMoves(Board& board, int turn);
};