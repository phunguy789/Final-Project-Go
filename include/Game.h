#pragma once
#include "Board.h"
#include "AI.h"
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;
#define pii pair<int, int> 
class Game
{
    public:
    Board board;
    AI ai;
    int turn;
    int mode;
    int difficult;
    bool gameOver;
    int passCount;
    stack<Board> undoStack;
    stack<Board> redoStack;

    Game();

    void reset();
    bool playMove(int i, int j);
    void passTurn();
    bool checkGameOver();
    int calculateScore();

    bool isValidMove(int i, int j);
    vector<pii> getGroup(int i, int j);
    int countLiberties(vector<pii> &group);
    int captureGroups(int i, int j);
    bool checkKo(int i, int j);

    void undo();
    void redo();

    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);

    private:
    int d1[4] = {1, -1, 0, 0},
        d2[4] = {0, 0, 1, -1};
    bool vis[N][N];
    void dfs(int u, int v, vector<pii> &interconnected, int color);
};