

#ifndef FIELD_H
#define	FIELD_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string.h>
#include <stdio.h>
#include "Dialog.h"
#include "Plane.h"

class Field {
public:
    Field(sf::RenderWindow  *refwindow);
    ~Field();
    void loop();
    bool handleEvents();
private:

    Plane* plane1;
    Plane* plane2;
    
    sf::Image field_image;
    sf::Sprite field_sprite;
    
    
    sf::RenderWindow* _window;
};

#endif	/* FIELD_H */

