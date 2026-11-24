#include "AI.h"
#include "Board.h"
#include "Game.h"
#include <vector>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <queue>
using namespace std;
using pii = pair<int, int>;
#define fi first 
#define se second
AI::AI()
{
}
vector<pii> AI::getLegalMoves(Board &board, int turn, Game &game)
{
    vector<pii> empty_pos;
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    if (game.completeMove(board, i, j, turn, 1)) 
        empty_pos.push_back({i, j});
    return empty_pos;
}
int AI::connectivityScore(Board& board, int i, int j, int turn, Game& game)
{
    vector<vector<pii>> groups;
    for (int k = 0; k < 4; k++)
    {
        int x = i + game.d1[k];
        int y = j + game.d2[k];
        if (min(x, y) < 0 || max(x, y) >= N) continue;
        if (board.a[x][y] != turn) continue;
        vector<pii> group = game.getGroup(board, x, y);
        bool found = false;
        for (auto &g : groups)
        {
            if (g == group)
            {
                found = true;
                break;
            }
        }
        if (!found) groups.push_back(group);
    }
    if (groups.size() >= 2) return 10;
    if (groups.size() == 1) return 2;
    return 0;
}
int AI::evaluate(Board &board, int aiturn, Game &game)
{
    int scores = 0;

    int black = 0, white = 0;
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    if (board.a[i][j] == 1) black++;
    else if (board.a[i][j] == 2) white++;
    if (aiturn == 1) scores += 10 * (black - white);
    else scores += 10 * (white - black);

    black = 0; white = 0;
    int capturedBlack = 0, capturedWhite = 0;
    int safe[3] = {};
    memset(game.par_vis, 0, sizeof game.par_vis);
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    if (game.par_vis[i][j] == 0 && board.a[i][j] != 0)
    {
        vector<pii> group = game.getGroup(board, i, j);
        int tmp = game.countLiberties(board, group);
        if (board.a[i][j] == 1) black += tmp;
        else white += tmp;
        if (tmp > 4) tmp = 4;
        safe[board.a[i][j]] += game.calScore[tmp];
        if (tmp == 1)
        {
            if (game.completeMove(board, game.tempPos.fi, game.tempPos.se, 3 - board.a[i][j], 1))
            {
                if (aiturn == 3 - board.a[i][j]) scores += 15;
                else scores -= 15;
            }
        }
    }
    if (aiturn == 1) 
    scores += 2 * (black - white) + 3 * (safe[1] - safe[2]);
    else scores += 2 * (white - black) + 3 * (safe[2] - safe[1]);

    int territoryBlack = 0;
    int territoryWhite = 0;
    bool territoryVis[N][N] = {};
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        if (board.a[i][j] != 0 || territoryVis[i][j]) continue;
        queue<pii> q;
        q.push({i, j});
        territoryVis[i][j] = true;
        int cnt = 0;
        bool borderBlack = false;
        bool borderWhite = false;
        while (!q.empty())
        {
            pii u = q.front();
            q.pop();
            cnt++;
            for (int k = 0; k < 4; k++)
            {
                int x = u.first + game.d1[k];
                int y = u.second + game.d2[k];
                if (min(x, y) < 0 || max(x, y) >= N) continue;
                if (board.a[x][y] == 1) borderBlack = true;
                else if (board.a[x][y] == 2) borderWhite = true;
                else if (!territoryVis[x][y])
                {
                    territoryVis[x][y] = true;
                    q.push({x, y});
                }
            }
        }
        if (borderBlack && !borderWhite) territoryBlack += cnt;
        else if (borderWhite && !borderBlack) territoryWhite += cnt;
    }
    if (aiturn == 1) scores += 2 * (territoryBlack - territoryWhite);
    else scores += 2 * (territoryWhite - territoryBlack);

    return scores;
}
int AI::minimaxAB(Board &board, int depth, int turn, int aiturn, int alpha, int beta, Game &game)
{
    if (depth == 0) return evaluate(board, aiturn, game);
    int bestscore = 0;
    bool maximize = (aiturn == turn);
    vector<pii> moves = getCandidateMoves(board, turn, game);
    if (moves.empty()) return evaluate(board, aiturn, game);
    if (maximize) bestscore = INT_MIN;
    else bestscore = INT_MAX;
    for (pii move : moves)
    {
        int i = move.fi, j = move.se;
        if (board.a[i][j] == 0)
        {
            Board oldboard = board;
            if (!game.completeMove(board, i, j, turn, 0)) 
            { board = oldboard; continue; }
            game.undoStack.push({board, {-1, -1}});
            int score = minimaxAB(board, depth - 1, 3 - turn, aiturn, alpha, beta, game);
            score += connectivityScore(board, i,j, turn, game);
            board = oldboard;
            game.undoStack.pop();
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
        Board oldboard = board;
        if (!game.completeMove(board, i, j, aiTurn, 0)) 
        { board = oldboard; continue; }
        game.undoStack.push({board, {-1, -1}});
        int score = minimaxAB(board, depth - 1, 3 - aiTurn, aiTurn, alpha, beta, game);
        score += connectivityScore(board, i, j, aiTurn, game);
        board = oldboard;
        game.undoStack.pop();
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
        vector<pii> empty_pos = getLegalMoves(board, turn, game);
        int pos = rand() % (empty_pos.size());
        int x, y;
        x = empty_pos[pos].fi; 
        y = empty_pos[pos].se;
        game.tempval = game.playMove(board, x, y, turn); 
        game.white += game.tempval;
        return {x, y};
    }
    else if (difficult == 2)
    {
        int depth = 1;
        pii move = findBestMove(board, depth, turn, game);
        game.tempval = game.playMove(board, move.fi, move.se, turn);
        game.white += game.tempval;
        return move;
    }
    else if (difficult == 3)
    {
        int depth = 2;
        pii move = findBestMove(board, depth, turn, game);
        game.tempval = game.playMove(board, move.fi, move.se, turn);
        game.white += game.tempval;
        return move;
    }
    return {0, 0};
}
vector<pii> AI::getCandidateMoves(Board& board, int turn, Game &game)
{
    vector<pii> legal = getLegalMoves(board, turn, game);
    vector<pii> candidates;
    bool near[N][N] = {};
    bool hasStone = false;
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        if (board.a[i][j] == 0) continue;
        hasStone = true;
        for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
        {
            int x = i + dx;
            int y = j + dy;
            if (game.completeMove(board, x, y, turn, 1)) 
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