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

    enum EventType { ZOOMIN, ZOOMOUT, EXIT, LMOUSE_PRESS, LMOUSE_RELEASE, DRAG };
    typedef struct {
        static const int MAX_ARGS = 4;
        int argn;
        EventType type;
        float args[MAX_ARGS];
    } Event;

private:
    InputHandler();

    static InputHandler* _instance;
    sf::RenderWindow* _window;
    Game* _game;
    Event _event;

    sf::Event _lastEvent;
};

#endif // INPUTHANDLER_H
