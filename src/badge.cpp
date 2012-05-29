/* 
 * File:   badge.cpp
 * Author: malcom
 * 
 * Created on May 29, 2012, 4:43 PM
 */

#include "badge.h"

badge::badge(sf::RenderWindow *refwindow,float posx,float posy) {
    
    _window=refwindow;
    _xpos=posx;
    _ypos=posy;
    
    _badgeColor= sf::Color(255,0,0);
    _shape= sf::Shape::Circle(_xpos,_ypos,20.0f,_badgeColor,2.0f,sf::Color(255,255,255));
           
}


badge::~badge() {
}


void badge::draw() {
    
    _window->Draw(_shape);
    
}
