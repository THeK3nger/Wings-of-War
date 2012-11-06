#ifndef GAME_H
#define	GAME_H

#include "SplashScreen.h"

struct GAME_configuration
{
	int search_depth;
	int E_distance;
	int E_visibility;
	int E_health;
};

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
    // WARNING: To avoid problem in input handling this value is overvalued.

    /*!
     * \brief SKIP_TICKS is the amount of ticks to the next frame.
     */
    static const double SKIP_TICKS = 1000/FRAME_PER_SECOND;

    /*!
     * \brief MAX_FRAME_SKIP is the maximum number of skippable frames.
     */
    static const double MAX_FRAME_SKIP = 10;

    static GAME_configuration conf;

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

    static sf::RenderWindow& getMainWindow();


private:
    /*!
     * Window height*width*color_depth + name
     */
    int height;
    int width;
    int depth;

    SplashScreen* splashscreen;
    Dialog* dialog;

    /*!
     * Possible states of the game
     */
    enum GameState {
        Uninitialized, ShowingSplash, ShowingMenu, Exiting
    };

    /*!
     * Actual state of the game
     */
    GameState _gameState;

    /*!
     * Render window
     */
    static sf::RenderWindow _mainWindow;

    /*!
     * \brief _clock represent the internal clock of the game.
     */
    sf::Clock _clock;

    /*!
     * Game exit routine
     */
    void exit();

    /*!
     * Draw the scene
     */
    void draw();

    /*!
     * \brief Update the game status
     */
    void update();

    /*!
     * Game initialization routine != from the alloc/init of the constructor
     */
    void init();
};



#endif	/* GAME_H */

