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
    void setMessage(std::string);
    void setDetails(std::string);
private:
    
    sf::String message;
    sf::String detail;
    sf::Font font;
    
    sf::Shape rect;
    
    sf::RenderWindow* _window;
    
    sf::Image iCats;
    sf::Sprite sCats, sCatsShadow;

};

#endif	/* KICKER_H */

