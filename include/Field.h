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
#include "Animation.h"
#include "CardImage.h"

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
    
    sf::Event lastEvent;        // used to store the last event
    
    Kicker * kicker;
    
    sf::Image field_image;
    sf::Sprite field_sprite;
    sf::Clock theClock;
    sf::Music _bgmusic;
    enum States {
        INIT, PLAYER_SELECT, BRAIN_SELECT, APPLY_MOVES, ANIM_MOVES, COMPUTE_DAMAGES, ANIM_DAMAGES, CHECK_FINISH
    };

    States CurrentState;

    sf::RenderWindow* _window;
    sf::View camera;
    
    bool _mouse_down;
    
    std::vector<CardImage*> cards;
    std::vector<sf::Rect<int> *> clickableAreas;
    
    int _xstart;
    int _ystart;
    int _xdisplacement;
    int _ydisplacement;
    
    WaterTile* water;
    
    std::map<int,int> cardmaster;
    std::map<int,int>::iterator it;
    int cardCounter;
};

#endif	/* FIELD_H */

