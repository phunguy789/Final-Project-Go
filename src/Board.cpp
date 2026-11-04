#include "Board.h"
#include <cstring>
#define pb push_back
#define fi first 
#define se second
using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};   

Board::Board(int n){reset(n);}

void Board::reset(int n){
    size = n; 
    if (n != 9 && n != 13 && n != 19) size = 19; 
    for (int r = 0; r < N; r++) for (int c = 0; c < N; c++) a[r][c] = EMPTY;
}

bool Board::inside(int r, int c) const {return 0 <= r && r < size && 0 <= c && c < size;}

Group Board::group(int r, int c) const{
    Group g; 
    if (!inside(r, c) || a[r][c] == EMPTY) return g; 
    bool seen[N][N] = {}, liberty[N][N] = {};
    g.stones.pb({r, c}); seen[r][c] = true;
    for (int i = 0; i < g.stones.size(); i++){
        int x = g.stones[i].fi, y = g.stones[i].se; 
        for (int j = 0; j < 4; j++){
            int dr = x + dx[j], dc = y + dy[j]; 
            if (!inside(dr, dc)) continue; 
            if (a[dr][dc] == EMPTY){
                // add each empty liberty only once
                if (!liberty[dr][dc]){ 
                    liberty[dr][dc] = true; 
                    g.liberties.pb({dr, dc});
                }
                else if (a[dr][dc] == a[r][c] && !seen[dr][dc]){ 
                    // add unvisited stones of same color
                    seen[dr][dc] = true; 
                    g.stones.pb({dr, dc});
                }
            }
        }
    }
    return g;
}

string Board::key() const{
    string res;
    for (int r = 0; r < size; r++) for (int c = 0; c < size; c++) res += char('0' + a[r][c]);
    return res;
}
