/* 
 * File:   WaterTile.h
 * Author: malcom
 *
 * Created on May 19, 2012, 12:57 PM
 */

#ifndef WATERTILE_H
#define	WATERTILE_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string.h>
#include <stdio.h>


class WaterTile {
public:
    WaterTile(sf::RenderWindow *refWindow);

    void update();
    virtual ~WaterTile();
    void setPos(float x, float y);
    
    sf::Sprite getSprite();
    
private:

    float timer;
    float acc;
    
    int xpos;
    int ypos;
    
    sf::IntRect frame1;
    sf::IntRect frame2;
    
    enum FrameState{one,two};
    FrameState currentFrame;
    
    sf::Clock Clock;
    sf::Image _spritesheet;
    sf::Sprite _sprite;
    sf::RenderWindow* _window;
    
};

#endif	/* WATERTILE_H */

