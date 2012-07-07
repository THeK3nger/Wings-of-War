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

    _gameState = Game::Uninitialized;
}

/*!
 * Game initialization routine != from the alloc/init of the constructor
 * 
 * Workflow;
 * init is public, called in the mainfile of the application.
 * init instantiate the main windows, then sets the game state to PLAYING 
 * and calls the "run" method.
 */
void Game::init() {
    LOGMESSAGE_NO_ENDL("Initializing Game...");
    if (_gameState != Game::Uninitialized) return;

    _mainWindow.Create(sf::VideoMode(width, height, depth), "Wings of War");
    _gameState = Game::Playing; //NOTE: Why there is this useless status update?
    _gameState = Game::ShowingSplash;
    OK;
    LOGMESSAGE("Starting Game Loop");
    while (_gameState != Game::Exiting) {
        this->run();
    }
    LOGMESSAGE("Game Exit Correctly!");
}

/*!
 * Game exit routine, not useful right now, but maybe... in the future...
 */
void Game::exit() {

}

/*!
 * Game loop routine
 */
void Game::run() {
    switch (_gameState) {
        case Game::Playing:
        {
            _mainWindow.Clear(sf::Color(0, 0, 0));
            _mainWindow.Display();
            this->CheckForEvents();
        }

        case Game::ShowingSplash:
        {

            splashscreen = new SplashScreen(&_mainWindow);
            splashscreen->loop();
            _gameState = Game::Exiting;
            delete splashscreen;
            
        }


            break;
    }

}

/*!
 *Events handler routine
 */
void Game::CheckForEvents() {
    sf::Event Event;
    if (_mainWindow.GetEvent(Event)) {
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) {
            //game state setted on EXITING
            _gameState = Game::Exiting;
        }
    }

}

Game::~Game() {
}

