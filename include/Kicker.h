#ifndef KICKER_H
#define	KICKER_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string.h>
#include <stdio.h>

class Kicker {
public:
    Kicker(sf::RenderWindow *refwindow);
    virtual ~Kicker();
    //experimental
    int run(); //bloccante
    void display(); //non bloccante
private:

    sf::RenderWindow* _window;
    
    sf::Image iCats;
    sf::Sprite sCats;

};

#endif	/* KICKER_H */

