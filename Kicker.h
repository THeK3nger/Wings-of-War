/* 
 * File:   Kicker.h
 * Author: malcom
 *
 * Created on May 17, 2012, 5:26 PM
 */

#ifndef KICKER_H
#define	KICKER_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string.h>
#include <stdio.h>


class Kicker {
public:
    Kicker(sf::RenderWindow  *refwindow);
    virtual ~Kicker();
    int run();
private:
    
    sf::RenderWindow* _window;

};

#endif	/* KICKER_H */
