#ifndef FIELD_H
#define	FIELD_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string.h>
#include <stdio.h>
#include "Dialog.h"
#include "Plane.h"
#include "WoWBrain.h"
#include "World.h"
#include "math.h"
#include "Kicker.h"

class Field {
public:
    Field(sf::RenderWindow *refwindow);
    ~Field();
    void loop();
    bool handleEvents();
private:

    Plane* plane1;
    Plane* plane2;

    WoWBrain* theBrain;
    World* theWorld;

    sf::Image field_image;
    sf::Sprite field_sprite;

    enum States {
        playerSelect, brainSelect, move, init
    };

    States CurrentState;

    sf::RenderWindow* _window;

    bool _mouse_down;

    int _xstart;
    int _ystart;
    int _xdisplacement;
    int _ydisplacement;
};

#endif	/* FIELD_H */

