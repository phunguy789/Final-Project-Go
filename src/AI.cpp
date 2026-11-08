#include "AI.h"
#include "Board.h"
#include "Game.h"
#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;
using pii = pair<int, int>;
AI::AI()
{
}
vector<pii> AI::getLegalMoves(Board &board, int turn)
{
    vector<pii> empty_pos;
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    if (board.a[i][j] == 0) empty_pos.push_back({i, j});
    return empty_pos;
}
int AI::evaluate(Board &board, int aiturn)
{
    int scores = 0;
    int black = 0, white = 0;
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    if (board.a[i][j] == 1) black++;
    else if (board.a[i][j] == 2) white++;
    if (aiturn == 1) scores = black - white;
    else scores = white - black;
    return scores;
}
int AI::minimax(Board &board, int depth, int turn, int aiturn)
{
    if (depth == 0) return evaluate(board, aiturn);
    int bestscore = 0;
    bool maximize = (aiturn == turn);
    bool foundmove = 0;
    if (maximize)
    {
        bestscore = INT_MIN;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        if (board.a[i][j] == 0)
        {
            foundmove = 1;
            board.a[i][j] = turn;
            int score = minimax(board, depth - 1, 3 - turn, aiturn);
            board.a[i][j] = 0;
            bestscore = max(bestscore, score);
        }
        if (!foundmove)
        bestscore = evaluate(board, aiturn);
    }
    else 
    {
        bestscore = INT_MAX;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        if (board.a[i][j] == 0)
        {
            foundmove = 1;
            board.a[i][j] = turn;
            int score = minimax(board, depth - 1, 3 - turn, aiturn);
            board.a[i][j] = 0;
            bestscore = min(bestscore, score);
        }
        if (!foundmove)
        bestscore = evaluate(board, aiturn);
    }
    return bestscore;
}
pii AI::findBestMove(Board& board, int depth, int aiTurn)
{
    int bestscore = INT_MIN;
    pair<int, int> bestmove = {-1, -1};
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    if (board.a[i][j] == 0)
    {
        board.a[i][j] = aiTurn;
        int score = minimax(board, depth - 1, 3 - aiTurn, aiTurn);
        board.a[i][j] = 0;
        if (score > bestscore)
        {
            bestscore = score;
            bestmove = {i, j};
        }
    }
    return bestmove;
}
pii AI::makemove(Board &board, int turn, int difficult)
{
    if (difficult == 1)
    {
        vector<pii> empty_pos = getLegalMoves(board, turn);
        int pos = rand() % (empty_pos.size());
        int x, y;
        board.a[x = empty_pos[pos].first][y = empty_pos[pos].second] = turn;
        return {x, y};
    }
    else if (difficult == 2)
    {
        pii move = findBestMove(board, 2, turn);
        board.a[move.first][move.second] = turn;
        return move;
    }
    return {0, 0};
}