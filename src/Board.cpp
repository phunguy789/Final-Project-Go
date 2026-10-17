#include "Board.h"
#include <cstring>
using namespace std;
Board::Board()
{
    reset();
}
void Board::reset()
{
    memset(a, 0, sizeof a);
}
