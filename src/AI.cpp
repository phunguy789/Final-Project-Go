#include "AI.h"
#include "Board.h"
#include "Game.h"
#include <vector>
#include <cstdlib>
#include <climits>
#include <iostream>
using namespace std;
using pii = pair<int, int>;
#define fi first 
#define se second
AI::AI()
{
}
vector<pii> AI::getLegalMoves(Board &board)
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
int AI::minimaxAB(Board &board, int depth, int turn, int aiturn, int alpha, int beta, Game &game)
{
    if (depth == 0) return evaluate(board, aiturn);
    int bestscore = 0;
    bool maximize = (aiturn == turn);
    vector<pii> moves = getCandidateMoves(board, turn, game);
    if (moves.empty()) return evaluate(board, aiturn);
    if (maximize) bestscore = INT_MIN;
    else bestscore = INT_MAX;
    for (pii move : moves)
    {
        int i = move.fi, j = move.se;
        if (board.a[i][j] == 0)
        {
            board.a[i][j] = turn;
            int score = minimaxAB(board, depth - 1, 3 - turn, aiturn, alpha, beta, game);
            board.a[i][j] = 0;
            // rollback
            if (maximize)
            {
                bestscore = max(bestscore, score);
                alpha = max(alpha, bestscore);
            }
            else 
            {
                bestscore = min(bestscore, score);
                beta = min(beta, bestscore);
            }
            if (beta <= alpha) break;
        }
    }
    return bestscore;
}
pii AI::findBestMove(Board& board, int depth, int aiTurn, Game &game)
{
    int bestscore = INT_MIN;
    pii bestmove = {-1, -1};
    vector<pii> candidateMoves = getCandidateMoves(board, aiTurn, game);
    int alpha = INT_MIN, beta = INT_MAX;
    for (pii move : candidateMoves)
    {
        int i = move.fi, j = move.se;
        board.a[i][j] = aiTurn;
        int score = minimaxAB(board, depth - 1, 3 - aiTurn, aiTurn, alpha, beta, game);
        board.a[i][j] = 0;
        // rollback
        if (score > bestscore)
        {
            bestscore = score;
            bestmove = move;
        }
        alpha = max(alpha, bestscore);
    }
    return bestmove;
}
pii AI::makemove(Board &board, int turn, int difficult, Game &game)
{
    if (difficult == 1)
    {
        vector<pii> empty_pos = getLegalMoves(board);
        int pos = rand() % (empty_pos.size());
        int x, y;
        board.a[x = empty_pos[pos].fi][y = empty_pos[pos].se] = turn;
        return {x, y};
    }
    else if (difficult == 2)
    {
        pii move = findBestMove(board, 1, turn, game);
        board.a[move.fi][move.se] = turn;
        return move;
    }
    return {0, 0};
}
vector<pii> AI::getCandidateMoves(Board& board, int turn, Game &game)
{
    vector<pii> legal = getLegalMoves(board);
    vector<pii> candidates;
    bool near[N][N] = {};
    bool hasStone = false;
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        if (board.a[i][j] == 0) continue;
        cout << i << " " << j << "\n";
        hasStone = true;
        for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
        {
            int x = i + dx;
            int y = j + dy;
            if (game.isValidMove(board, x, y, turn)) 
            // if (min(x, y) < 0 || max(x, y) >= N) continue;
            near[x][y] = true;
        }
    }
    if (!hasStone)
    {
        for (pii pos : legal)
        if (pos.fi == N / 2 && pos.se == N / 2) return {pos};
        return legal;
    }
    for (pii pos : legal)
    {
        int x = pos.fi;
        int y = pos.se;
        if (near[x][y]) candidates.push_back(pos);
    }
    if (candidates.empty()) return legal;
    return candidates;
}