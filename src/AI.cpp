#include "AI.h"
#include "Board.h"
#include <cstring>
#include <vector>
#include <cstdlib>
#define pii pair<int, int>
using namespace std;
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
int AI::evaluate(Board &board, int turn)
{
    int scores = 0;
    return scores;
}
int AI::minimax(Board &board, int depth, int turn, int aiturn)
{
    return 0;
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
        
    }
    return {0, 0};
}