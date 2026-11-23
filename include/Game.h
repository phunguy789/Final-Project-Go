#pragma once
#include "Board.h"
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;
using pii = pair<int, int>;
struct stackElement
{
    Board board;
    pii highlight;
    int passCount;
};
class Game
{
    public:
    //setting
    int boardTheme = 0;
    // 0 = classic , 1 = dark , 2 = light
    int stoneTheme = 0;
    // 0 = classic , 1 = cartoon
    bool soundEnabled = 1;
    bool musicEnabled = 1;
    float soundVolume = 60.f;
    float musicVolume = 60.f;
    //
    Board board;
    int turn;
    int mode; // 1 = pvp, 2 = pve
    int difficult;
    bool gameOver;
    int passCount;
    stack<stackElement> undoStack;
    stack<stackElement> redoStack;

    bool par_vis[N][N];
    pii tempPos, highlight;
    int calScore[5] = {0, -15, -5, 2, 3};

    Game();

    void reset();
    bool playMove(Board &board, int i, int j, int turn);
    void passTurn();
    bool checkGameOver();
    pii calculateScore();

    bool completeMove(Board &board, int i, int j, int turn, bool rollback);
    vector<pii> getGroup(Board &board, int i, int j);
    int countLiberties(Board &board, vector<pii> &group);
    int captureGroups(Board &board, int i, int j);
    bool checkKo(Board &board, int i, int j);
    bool isSuicide(Board &board, int i, int j);

    void undo();
    void redo();
    bool isSameBoard(Board &This, Board &That);

    bool saveGame(string filename);
    bool loadGame(string filename);

    int d1[4] = {1, -1, 0, 0},
        d2[4] = {0, 0, 1, -1};

    private:
    bool vis[N][N];
    void dfs(Board &board, int u, int v, vector<pii> &interconnected, int color);
};