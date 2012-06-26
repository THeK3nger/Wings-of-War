#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Game.h"

class InputHandler
{
public:
    static InputHandler* createInputHandler(sf::RenderWindow* window,Game* game);
    static InputHandler* getSingleton();
    void handleInput();
private:
    InputHandler();

    static InputHandler* _instance;
    sf::RenderWindow* _window;
    Game* _game;

    sf::Event lastEvent;
};

#endif // INPUTHANDLER_H
