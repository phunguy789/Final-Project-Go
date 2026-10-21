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
pii AI::makemove(Board &board, int turn, int difficult)
{
    if (difficult == 1)
    {
        vector<pii> g;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        if (board.a[i][j] != 0) g.push_back({i, j});
        int pos = rand() % (g.size());
        int x, y;
        board.a[x = g[pos].first][y = g[pos].second] = turn;
        return {x, y};
    }
    else if (difficult == 2)
    {
        
    }
    return {0, 0};
}