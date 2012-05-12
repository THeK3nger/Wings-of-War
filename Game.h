#ifndef GAME_H
#define	GAME_H

#include "Plane.h"
#include "World.h"
#include "WoWBrain.h"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


/*!
 * \brief This class is the core class of the Game.
 * 
 * It contains various stuff to execute the game.
 */
class Game {
public:
    
    /*!
     * Costructor for the class Game.
     * Basically here we define all the parameters to instantiate a window 
     * \param int   h=height
     * \param int   w=width
     * \param int   d=depth
     * \param char* n=name
     */
    
    Game(int h, int w, int d);
    
    Game(const Game& orig);
    
    virtual ~Game();
    
    
    /*!
     * Game initialization routine != from the alloc/init of the constructor
     */
    void init();
    
    
    /*!
     * Main loop for the game
     */
    void run();
    
    
private:
    World* world;
    WoWBrain* ai;
    
    /*!
     * Window height*width*color_depth + name
     */
    int height;
    int width;
    int depth;
    char name[100];
    
    /*!
     * Possible states of the game
     */
    enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };
    
    /*!
     * Actual state of the game
     */
 
     GameState _gameState;
    
    /*!
     * Render window
     */
     sf::RenderWindow _mainWindow;
};

#endif	/* GAME_H */

