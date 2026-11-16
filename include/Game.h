#pragma once
#include "Board.h"
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;
using pii = pair<int, int>;
class Game
{
    public:
    Board board;
    int turn;
    int mode; // 1 = pvp, 2 = pve
    int difficult;
    bool gameOver;
    int passCount;
    bool par_vis[N][N];
    pii tempPos, highlight;
    int calScore[5] = {0, -15, -5, 2, 3};
    stack<pair<Board, int>> undoStack;
    stack<pair<Board, int>> redoStack;

    Game();

    void reset();
    bool playMove(Board &board, int i, int j, int turn);
    void passTurn();
    bool checkGameOver();
    int calculateScore();

    bool completeMove(Board &board, int i, int j, int turn, bool rollback);
    vector<pii> getGroup(Board &board, int i, int j);
    int countLiberties(Board &board, vector<pii> &group);
    int captureGroups(Board &board, int i, int j);
    bool checkKo(Board &board, int i, int j);
    bool isSuicide(Board &board, int i, int j);

    void undo();
    void redo();
    bool isSameBoard(Board &This, Board &That);

    void printBoard(Board &board, string &filename);
    bool saveGame(string &filename);
    bool loadGame(string &filename);

    int d1[4] = {1, -1, 0, 0},
        d2[4] = {0, 0, 1, -1};

    private:
    bool vis[N][N];
    void dfs(Board &board, int u, int v, vector<pii> &interconnected, int color);
};