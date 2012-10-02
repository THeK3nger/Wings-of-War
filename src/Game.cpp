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
    splashscreen = new SplashScreen(&_mainWindow);
    OK;
}

/*!
 * MAIN GAME LOOP
 */
void Game::mainGameLoop() {
    this->init();

    long next_step_time = getTicks();
    int loop = 0;

    LOGMESSAGE("Starting Game Loop");
    while (_gameState != Game::Exiting) {
        loop = 0;
        while ((getTicks()>next_step_time) && (loop<Game::MAX_FRAME_SKIP)) {
            this->update();
            next_step_time += Game::SKIP_TICKS;
            loop++;
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
    switch (_gameState) {
        case Game::Playing:
        {
            _mainWindow.Clear(sf::Color(0, 0, 0));
            _mainWindow.Display();
            this->CheckForEvents();
        }

        case Game::ShowingSplash:
        {
            splashscreen->draw();
        }
    default :
            break;
    }
    //displaying on the window
    _mainWindow.Display();
}

void Game::update() {
    if (splashscreen->isExiting()) {
        _gameState = Game::Exiting;
    }
    switch (_gameState) {
        case Game::Playing:
            this->CheckForEvents();
            break;

        case Game::ShowingSplash:
            splashscreen->update();
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
    delete splashscreen;
}

