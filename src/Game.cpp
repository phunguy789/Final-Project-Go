#include <fstream>
#include <iostream>
#include <cstring>
#include <queue>
#include "Game.h"
#include "Board.h"
using namespace std;
using pii = pair<int, int>;
#define fi first
#define se second
// int debug
Game::Game()
{
    reset();
}
void Game::reset()
{
    board.reset(19);     
    black = white = 0;  
    turn = 2;         
    gameOver = false;    
    passCount = 0; 
    highlight = {-1, -1};      
    while (!undoStack.empty()) undoStack.pop();
    while (!redoStack.empty()) redoStack.pop();
    undoStack.push({board, {-1, -1}, 0});
}
int Game::playMove(Board &board, int i, int j, int turn)
{
    board.a[i][j] = turn;
    return captureGroups(board, i, j);
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
pii Game::calculateScore()
{
    int territoryBlack = 0;
    int territoryWhite = 0;
    bool territoryVis[N][N] = {};
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        if (board.a[i][j] != 0 || territoryVis[i][j]) continue;
        queue<pii> q;
        q.push({i, j});
        territoryVis[i][j] = true;
        int cnt = 0;
        bool borderBlack = false;
        bool borderWhite = false;
        while (!q.empty())
        {
            pii u = q.front();
            q.pop();
            cnt++;
            for (int k = 0; k < 4; k++)
            {
                int x = u.first + d1[k];
                int y = u.second + d2[k];
                if (min(x, y) < 0 || max(x, y) >= N) continue;
                if (board.a[x][y] == 1) borderBlack = true;
                else if (board.a[x][y] == 2) borderWhite = true;
                else if (!territoryVis[x][y])
                {
                    territoryVis[x][y] = true;
                    q.push({x, y});
                }
            }
        }
        if (borderBlack && !borderWhite) territoryBlack += cnt;
        else if (borderWhite && !borderBlack) territoryWhite += cnt;
    }
    black += territoryBlack;
    white += territoryWhite;
    return {black, white};
}
bool Game::checkKo(Board &board, int i, int j)
{
    if ((int)undoStack.size() < 2) return 0; 
    stackElement state_before = undoStack.top();
    undoStack.pop();
    if (isSameBoard(undoStack.top().board, board))
    {
        undoStack.push(state_before);
        return 1;
    }
    undoStack.push(state_before);
    return 0;
}
bool Game::isSuicide(Board &board, int i, int j)
{
    vector<pii> group = getGroup(board, i, j);
    if (countLiberties(board, group) == 0) return 1;
    return 0;
}
bool Game::completeMove(Board &board, int i, int j, int turn, bool rollback)
{
    if (min(i, j) < 0 || max(i, j) >= N) return 0;
    if (board.a[i][j] != 0) return 0;
    Board oldboard = board;
    tempval = playMove(board, i, j, turn);
    if (checkKo(board, i, j)) 
    {
        board = oldboard;
        return 0;
    }
    if (isSuicide(board, i, j))
    {
        board = oldboard;
        return 0;
    }
    if (rollback) board = oldboard;
    return 1;
}
void Game::dfs(Board &board, int u, int v, vector<pii> &interconnected, int color)
{
    vis[u][v] = par_vis[u][v] = 1;
    interconnected.push_back({u, v});
    for (int i = 0; i < 4; i++)
    {
        int newu = u + d1[i], newv = v + d2[i];
        if (min(newu, newv) < 0 || max(newu, newv) >= N 
            || vis[newu][newv] || board.a[newu][newv] != color) continue;
        dfs(board, newu, newv, interconnected, color);
    }
}
vector<pii> Game::getGroup(Board &board, int i, int j)
{
    vector<pii> interconnected;
    memset(vis, 0, sizeof vis);
    dfs(board, i, j, interconnected, board.a[i][j]);
    return interconnected;
}
int Game::countLiberties(Board &board, vector<pii> &group)
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
            if (board.a[newx][newy] == 0) tempPos = {newx, newy};
            vis[newx][newy] = 1;
        }
    }
    return Lib_count;
}
int Game::captureGroups(Board &board, int i, int j)
{
    int cnt_capture = 0;
    for (int p = 0; p < 4; p++)
    {
        int x = i + d1[p], y = j + d2[p];
        if (min(x, y) < 0 || max(x, y) >= N || board.a[x][y] == board.a[i][j])
            continue;
        if (board.a[x][y] == 0) continue;
        vector<pii> group = getGroup(board, x, y);
        if (countLiberties(board, group) == 0)
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
void Game::undo()
{
    if (mode == 1)
    {
        if (undoStack.size() < 2) return;
        stackElement tmp = undoStack.top();
        undoStack.pop();
        redoStack.push(tmp);
        tmp = undoStack.top();
        board = tmp.board; highlight = tmp.highlight; passCount = tmp.passCount;
        turn = 3 - turn;
    }
    else 
    {
        if (undoStack.size() < 3) return;
        stackElement tmp = undoStack.top();
        undoStack.pop();
        redoStack.push(tmp);
        tmp = undoStack.top();
        undoStack.pop();
        redoStack.push(tmp);
        tmp = undoStack.top();
        board = tmp.board; highlight = tmp.highlight; passCount = tmp.passCount;
    }
}
void Game::redo()
{
    if (mode == 1)
    {
        if (redoStack.empty()) return;
        stackElement tmp = redoStack.top();
        redoStack.pop();
        undoStack.push(tmp);
        board = tmp.board; highlight = tmp.highlight; passCount = tmp.passCount;
        turn = 3 - turn;
    }
    else 
    {
        if (redoStack.empty()) return;
        stackElement tmp = redoStack.top();
        redoStack.pop();
        undoStack.push(tmp);
        tmp = redoStack.top();
        redoStack.pop();
        undoStack.push(tmp);
        board = tmp.board; highlight = tmp.highlight; passCount = tmp.passCount;
    }
}
bool Game::saveGame(string filename)
{
    ofstream file(filename);
    if (!file.is_open()) return 0;

    file << turn << "\n";
    file << difficult << "\n";
    file << gameOver << "\n";

    stack<stackElement> tmp, rollback = undoStack;
    file << undoStack.size() << "\n";
    while (!undoStack.empty()) tmp.push(undoStack.top()), undoStack.pop();
    undoStack = rollback;
    while (!tmp.empty())
    {
        stackElement x = tmp.top();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) 
            file << x.board.a[i][j] << " ";
            file << "\n";
        }
        file << x.highlight.fi << " " << x.highlight.se << "\n";
        file << x.passCount << "\n";
        tmp.pop();
    }
    
    rollback = redoStack;
    file << redoStack.size() << "\n";
    while (!redoStack.empty()) tmp.push(redoStack.top()), redoStack.pop();
    redoStack = rollback;
    while (!tmp.empty())
    {
        stackElement x = tmp.top();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) 
            file << x.board.a[i][j] << " ";
            file << "\n";
        }
        file << x.highlight.fi << " " << x.highlight.se << "\n";
        file << x.passCount << "\n";
        tmp.pop();
    }

    file.close();
    return 1;
}
bool Game::loadGame(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) return 0;

    int temp;
    if (!(file >> temp)) return 0;

    turn = temp;
    file >> difficult;
    file >> gameOver;

    while (!undoStack.empty()) undoStack.pop();
    while (!redoStack.empty()) redoStack.pop();
    int sz;

    file >> sz;
    while (sz--)
    {
        stackElement tmp;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) file >> tmp.board.a[i][j];
        file >> tmp.highlight.fi >> tmp.highlight.se;
        file >> tmp.passCount;
        undoStack.push(tmp);
    }    

    file >> sz;
    while (sz--)
    {
        stackElement tmp;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) file >> tmp.board.a[i][j];
        file >> tmp.highlight.fi >> tmp.highlight.se;
        file >> tmp.passCount;
        redoStack.push(tmp);
    }  

    board = undoStack.top().board;
    highlight = undoStack.top().highlight;
    passCount = undoStack.top().passCount;

    file.close();
    return 1;
}
