#pragma once
#include "Board.h"
#include "AI.h"
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;
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
    std::vector<std::pair<int, int>> getGroup(int i, int j);
    int countLiberties(int i, int j);
    int captureGroups(int i, int j);
    bool checkKo(int i, int j);

    void undo();
    void redo();

    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);
};