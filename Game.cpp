#include "Game.h"
 /*!
 * Constructor:
 * sets the size and the depth of the window
 * sets the actual state
 */
Game::Game(int h, int w, int d) 
{
  width=w;
  height=h;
  depth=d;
  //name=n;
  
  _gameState = Game::Uninitialized;
    
}
 /*!
  * Game initialization routine != from the alloc/init of the constructor
 */
void Game::init()
{
    if(_gameState!=Game::Uninitialized) return;
    
    _mainWindow.Create(sf::VideoMode(width,height,depth),"Wings of War");
    _gameState = Game::Playing;
}
    
    
/*!
 * Drawing loop routine
 */
void Game::run()
{  
        _mainWindow.Clear(sf::Color(255,0,0));
        _mainWindow.Display();
}

Game::Game(const Game& orig) {
}

Game::~Game() {
}

