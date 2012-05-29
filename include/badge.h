/* 
 * File:   badge.h
 * Author: malcom
 *
 * Created on May 29, 2012, 4:43 PM
 */

#ifndef BADGE_H
#define	BADGE_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class badge {
public:
    badge(sf::RenderWindow *refwindow,float posx,float posy);
    virtual ~badge();
    void draw();
private:
    
    float _xpos;
    float _ypos;
    int _number;
    sf::Color _badgeColor;
    sf::Shape _shape;
    sf::RenderWindow* _window;
    sf::String _numberString;
    sf::Font _font;
};

#endif	/* BADGE_H */

