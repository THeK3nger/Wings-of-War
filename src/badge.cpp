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
    _shape= sf::Shape::Circle(_xpos,_ypos,15.0f,_badgeColor,3.0f,sf::Color(255,255,255));
    
    _font.LoadFromFile("assets/pixelmix.ttf");
    _numberString.SetFont(_font);
    _numberString.SetPosition(_xpos-5,_ypos-10);
    _numberString.SetSize(20.f);
    _numberString.SetText("1");
}


badge::~badge() {
}


void badge::draw() {
    
    _window->Draw(_shape);
    _window->Draw(_numberString);
    
}
