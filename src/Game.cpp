#include "Game.h"
using namespace std;
#define pii pair<int, int> 
#define fi first
#define se second
Game::Game()
{
    reset();
}
void Game::reset()
{
    board.reset();       
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
bool Game::isValidMove(int i, int j)
{
    if (min(i, j) < 0 || max(i, j) > N) return 0;
    if (board.a[i][j] != 0) return 0;
    // need add more conditions to check valid move
    return 1;
}
vector<pii> Game::getGroup(int i, int j)
{
    return {};
}
int Game::countLiberties(int i, int j)
{
    return 0;
}
int Game::captureGroups(int i, int j)
{
    return 0;
}
bool Game::checkKo(int i, int j)
{
    return 0;
}
void Game::undo()
{

}
void Game::redo()
{

}
bool Game::saveGame(const string& filename)
{
    return 0;
}
bool Game::loadGame(const string& filename)
{
    return 0;
}
