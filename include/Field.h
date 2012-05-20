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
#include <stdlib.h>
#include "WaterTile.h"

class Field {
public:
    Field(sf::RenderWindow *refwindow);
    ~Field();
    void loop();
    int handleEvents();
private:

    Plane* plane1;
    Plane* plane2;

    WoWBrain* theBrain;
    World* theWorld;

    sf::Image field_image;
    sf::Sprite field_sprite;
    sf::Clock theClock;
    sf::Music _bgmusic;
    enum States {
        playerSelect, brainSelect, move, init
    };

    States CurrentState;

    sf::RenderWindow* _window;
    sf::View camera;
    
    bool _mouse_down;
    
    //conto quante righe/colonne di sprite di field mi servono
    //per "riempire" il world
    int field_rows;
    int field_cols;
    
   
    int _xstart;
    int _ystart;
    int _xdisplacement;
    int _ydisplacement;
    
    WaterTile* water;
};

#endif	/* FIELD_H */

