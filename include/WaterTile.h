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
    int xpos;
    int ypos;

    int _frame_step;
    int _frame_count;
    
    sf::IntRect frame1;
    sf::IntRect frame2;
    sf::IntRect frame3;
    
    enum FrameState{one,two,three};
    FrameState currentFrame;
    
    sf::Image _spritesheet;
    sf::Sprite _sprite;
    sf::RenderWindow* _window;
    
};

#endif	/* WATERTILE_H */

