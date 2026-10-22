#pragma once
#include<string>
#include<utility>
#include<vector>
using namespace std; 

const int N = 19;
const int EMPTY = 0, BLACK = 1, WHITE = 2;

using pii = pair<int, int>;

// connected group and its liberties
struct Group{ 
    vector<pii> stones; 
    vector<pii> liberties; 
};

// in4 used for final scoring
struct Score{ 
    int stones[3]{};
    int territory[3]{};
    int removed[3]{}; 
    int owner[N][N]{};
    double black = 0, white = 0
};

class Board{
public:
    int a[N][N]{};
    int size;
    explicit Board(int n = 19); // constructor; default 19 x 19
    Board();
    void reset();
    bool inside(int r, int c) const;
    Group group(int r, int c) const;
    string key() const; 
    bool play(int r, int c, int color, const vector<string>& pos, vector<pii>& captured, string& error);
    bool eye(int r, int c, int color) const;
    Score score(const bool dead[N][N], double komi) const;
};
