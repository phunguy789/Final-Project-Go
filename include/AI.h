#pragma once
#include <Board.h>
#include <utility>
#define pii pair<int, int>
using namespace std;
class AI
{
    public:
    AI();
    pii makemove(Board &board, int turn, int difficult);
}