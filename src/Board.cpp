#include "Board.h"
#include <cstring>
using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};   

Board::Board(int n){reset(n);}

void Board::reset(int n){
    size = n; 
    if (n != 9 && n != 13 && n != 19) size = 19; 
    for (int r = 0; r < N; r++) for (int c = 0; c < N; c++) a[r][c] = EMPTY;
}

bool Board::inside(int r, int c) const {return 0 <= r && r < size && 0 <= c && c < size;}

string Board::key() const{
    string res;
    for (int r = 0; r < size; r++) for (int c = 0; c < size; c++) res += char('0' + a[r][c]);
    return res;
}
