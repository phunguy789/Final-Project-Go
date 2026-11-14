#pragma once
#include "Board.h"
#include "Game.h"
#include <vector>
#include <utility>
using namespace std;
class AI
{
    public:
    AI();
    pii makemove(Board &board, int turn, int difficult, Game &game);
    vector<pii> getLegalMoves(Board &board, int turn, Game &game);
    int evaluate(Board &board, int aiTurn, Game &game);
    int minimaxAB(Board &board, int depth, int turn, int aiTurn, int alpha, int beta, Game &game);
    pii findBestMove(Board& board, int depth, int aiTurn, Game &game);
    vector<pii> getCandidateMoves(Board& board, int turn, Game &game);
};