#include "Game.h"
#include "wowcommon.h"

/*!
 * Constructor:
 * sets the size and the depth of the window
 * sets the actual state
 */
Game::Game(int h, int w, int d) {
    width = w;
    height = h;
    depth = d;

    _clock = sf::Clock();
    _gameState = Game::Uninitialized;
}

/*!
 * Game initialization routine != from the alloc/init of the constructor
 *
 * Workflow;
 * init is public, called in `mainGameLoop`.
 * init instantiate the main windows, then sets the game state to PLAYING
 */
void Game::init() {
    LOGMESSAGE_NO_ENDL("Initializing Game...");
    if (_gameState != Game::Uninitialized) return;

    _mainWindow.Create(sf::VideoMode(width, height, depth), "Wings of War");
    _gameState = Game::ShowingSplash;
    splashscreen = new SplashScreen(&_mainWindow);
    OK;
}

/*!
 * MAIN GAME LOOP
 *
 * Perform Update at FRAME_PER_SECOND and Draw as fast as it can!
 */
void Game::mainGameLoop() {
    this->init();

    //long next_step_time = getTicks();
    long next_step_time = (long) ((_clock.GetElapsedTime() * 1000)+0.5);
    int loops;

    LOGMESSAGE("Starting Game Loop");
    while (_gameState != Game::Exiting) {
        loops = 0;
        long new_time = (long) ((_clock.GetElapsedTime() * 1000)+0.5);
        while ((new_time>next_step_time) && (loops<Game::MAX_FRAME_SKIP)) {
            LOGMESSAGE("LOL");
            this->update();
            next_step_time += Game::SKIP_TICKS;
            loops++;
        }
        this->draw();
    }
    LOGMESSAGE("Game Exit Correctly!");
}

/*!
 * Game exit routine, not useful right now, but maybe... in the future...
 */
void Game::exit() {

}

/*!
 * Game rendering routine
 */
void Game::draw() {
    // Clear Window
    _mainWindow.Clear(sf::Color(0,0,0));
    // Different draw for each state.
    // NOTE: Only One State.
    splashscreen->draw();
    //Displaying on the window
    _mainWindow.Display();
}

/*!
 * Game Update Routine
 */
void Game::update() {
    // If splashscreen is Exiting than Game is Exiting.
    if (splashscreen->isExiting()) {
        _gameState = Game::Exiting;
    }
    // Else update.
    splashscreen->update();
}

/*!
 * Destructor
 */
Game::~Game() {
    delete splashscreen;
}

