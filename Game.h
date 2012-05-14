#ifndef GAME_H
#define	GAME_H

#include "Plane.h"
#include "World.h"
#include "WoWBrain.h"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include <stdio.h>

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
    
    /*!
     * Destructor
     */
    virtual ~Game();
    
    
    /*!
     * Game initialization routine != from the alloc/init of the constructor
     */
    void init();
    
   
    
    /*!
     * Private side
     */
    
    
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
     
      /*!
     * Game exit routine
     */
    void exit();
    
    /*!
     * Main loop for the game
     */
    void run();
    
     /*!
     * Main loop for the game
     */
    void showSplashScreen();
    
    
     /*!
     * Events polling routine
     */
    void CheckForEvents();
};

#endif	/* GAME_H */

