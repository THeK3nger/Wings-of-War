#ifndef GAME_H
#define	GAME_H

#include "Plane.h"
#include "World.h"
#include "WoWBrain.h"
#include "SplashScreen.h"
#include "Dialog.h"

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
     * \brief FRAME_PER_SECOND is the desired fps of the game loop.
     */
    static const int FRAME_PER_SECOND = 50;

    /*!
     * \brief SKIP_TICKS is the amount of ticks to the next frame.
     */
    static const double SKIP_TICKS = 1000/FRAME_PER_SECOND;

    /*!
     * \brief MAX_FRAME_SKIP is the maximum number of skippable frames.
     */
    static const double MAX_FRAME_SKIP = 10;

    /*!
     * Costructor for the class Game.
     * Basically here we define all the parameters to instantiate a window 
     * \param int   h=height
     * \param int   w=width
     * \param int   d=depth
     */

    Game(int h, int w, int d);

    /*!
     * Destructor
     */
    virtual ~Game();

    /*!
     * \brief mainGameLoop starts the main game loop.
     */
    void mainGameLoop();

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

    SplashScreen* splashscreen;
    Dialog* dialog;

    /*!
     * Possible states of the game
     */
    enum GameState {
        Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting
    };

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
     * Draw the scene
     */
    void draw();

    /*!
     * \brief update the game status
     */
    void update();

    /*!
     * Events polling routine
     */
    void CheckForEvents();

    /*!
     * Game initialization routine != from the alloc/init of the constructor
     */
    void init();
};

#endif	/* GAME_H */

