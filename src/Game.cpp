#include <fstream>
#include <iostream>
#include <cstring>
#include "Game.h"
#include "Board.h"
using namespace std;
using pii = pair<int, int>;
#define fi first
#define se second
Game::Game()
{
    reset();
}
void Game::reset()
{
    board.reset(19);       
    turn = 2;            
    mode = 0;            
    difficult = 1;       
    gameOver = false;    
    passCount = 0;       
    while (!undoStack.empty()) undoStack.pop();
    while (!redoStack.empty()) redoStack.pop();
}
bool Game::playMove(int i, int j)
{
    return 0;
}
void Game::passTurn()
{
    passCount++;
    turn = 3 - turn;
}
bool Game::checkGameOver()
{
    if (passCount >= 2) return 1;
    return 0;
}
int Game::calculateScore()
{
    return 0;
}
bool Game::isSuicide(int i, int j)
{
    for (int p = 0; p < 4; p++)
    {
        int x = i + d1[p];
        int y = j + d2[p];
        if (min(x, y) < 0 || max(x, y) >= N) continue;
        if (board.a[i][j] == board.a[x][y] || board.a[x][y] == 0) continue;
        vector<pii> group = getGroup(x, y);
        if (countLiberties(group) == 0) return 0;        
    }
    vector<pii> group = getGroup(i, j);
    if (countLiberties(group) == 0) return 1;
    return 0;
}
bool Game::isValidMove(int i, int j, int turn)
{
    if (min(i, j) < 0 || max(i, j) >= N) return 0;
    if (board.a[i][j] != 0) return 0;
    if (checkKo(i, j)) return 0;
    board.a[i][j] = turn;
    if (isSuicide(i, j))
    {
        board.a[i][j] = 0;
        return 0;
    }
    board.a[i][j] = 0;
    return 1;
}
void Game::dfs(int u, int v, vector<pii> &interconnected, int color)
{
    vis[u][v] = 1;
    interconnected.push_back({u, v});
    for (int i = 0; i < 4; i++)
    {
        int newu = u + d1[i], newv = v + d2[i];
        if (min(newu, newv) < 0 || max(newu, newv) >= N 
            || vis[newu][newv] || board.a[newu][newv] != color) continue;
        dfs(newu, newv, interconnected, color);
    }
}
vector<pii> Game::getGroup(int i, int j)
{
    vector<pii> interconnected;
    memset(vis, 0, sizeof vis);
    dfs(i, j, interconnected, board.a[i][j]);
    return interconnected;
}
int Game::countLiberties(vector<pii> &group)
{
    memset(vis, 0, sizeof vis);
    int Lib_count = -(int)(group.size());
    for (pii &pos : group)
    {
        int x = pos.fi, y = pos.se;
        Lib_count += !vis[x][y];
        vis[x][y] = 1;
        for (int i = 0; i < 4; i++)
        {
            int newx = x + d1[i], newy = y + d2[i];
            if (min(newx, newy) < 0 || max(newx, newy) >= N) continue;
            if (board.a[newx][newy] > 0 && board.a[newx][newy] != board.a[x][y])
            continue;
            if (vis[newx][newy]) continue;
            Lib_count++;
            vis[newx][newy] = 1;
        }
    }
    return Lib_count;
}
int Game::captureGroups(int i, int j)
{
    int cnt_capture = 0;
    for (int i = 0; i < 4; i++)
    {
        int x = i + d1[i], y = j + d2[i];
        if (min(x, y) < 0 || max(x, y) >= N || board.a[x][y] == board.a[i][j])
            continue;
        vector<pii> group = getGroup(x, y);
        if (countLiberties(group) == 0)
        {
            cnt_capture += (int)group.size();
            for (pii &p : group) board.a[p.fi][p.se] = 0;
        }
    }
    return cnt_capture;
}
bool Game::isSameBoard(Board &This, Board &That)
{
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        if (This.a[i][j] != That.a[i][j]) return 0;
    return 1;
}
bool Game::checkKo(int i, int j)
{
    pair<Board, int> state_before = undoStack.top();
    undoStack.pop();
    if (isSameBoard(undoStack.top().fi, board))
    {
        undoStack.push(state_before);
        return 0;
    }
    undoStack.push(state_before);
    return 1;
}
void Game::undo()
{
    if (undoStack.empty()) return;
    pair<Board, int> state = undoStack.top();
    undoStack.pop();
    board = undoStack.top().fi;
    passCount = undoStack.top().se;
    redoStack.push(state);
}
void Game::redo()
{
    if (redoStack.empty()) return;
    pair<Board, int> state = redoStack.top();
    redoStack.pop();
    board = redoStack.top().fi;
    passCount = redoStack.top().se;
    undoStack.push(state);
}
void Game::printBoard(Board &board, string &filename)
{
    ofstream file(filename);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        file << board.a[i][j] << " ";
        cout << "\n";
    }
    file.close();
}
bool Game::saveGame(string &filename)
{
    ofstream file(filename);
    if (!file.is_open()) return 0;

    printBoard(board, filename);

    file << turn << "\n";
    file << mode << "\n";
    file << difficult << "\n";
    file << gameOver << "\n";
    file << passCount << "\n";

    file.close();
    return 1;
}
bool Game::loadGame(string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) return 0;

    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) file >> board.a[i][j];

    file >> turn;
    file >> mode;
    file >> difficult;
    file >> gameOver;
    file >> passCount;

    file.close();
    return 1;
}
