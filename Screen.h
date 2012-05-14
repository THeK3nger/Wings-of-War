/* 
 * File:   Screen.h
 * Author: malcom
 *
 * Created on May 14, 2012, 4:42 PM
 */

#ifndef SCREEN_H
#define	SCREEN_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <stdio.h>

class Screen {
public:
    Screen(sf::RenderWindow  *refwindow);
    virtual ~Screen();
    
    sf::RenderWindow* _window;
    
private:
    

};

#endif	/* SCREEN_H */

