#include "Game.h"
using namespace std;
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

}
bool Game::checkGameOver()
{
    return 0;
}
int Game::calculateScore()
{
    return 0;
}
bool Game::isValidMove(int i, int j)
{
    return 0;
}
vector<pair<int, int>> Game::getGroup(int i, int j)
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
