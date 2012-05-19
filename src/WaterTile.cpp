/* 
 * File:   WaterTile.cpp
 * Author: malcom
 * 
 * Created on May 19, 2012, 12:57 PM
 */

#include "WaterTile.h"

WaterTile::WaterTile(sf::RenderWindow *refWindow) {
    
    _window=refWindow;
    
    xpos=100;
    ypos=100;
    
    timer=10;
    acc=0;
    
    _spritesheet.LoadFromFile("assets/watertile.png");
    _sprite.SetImage(_spritesheet);
    
    frame1=sf::IntRect(16,16,31,31);
    frame2=sf::IntRect(48,16,63,31);
    
    currentFrame=WaterTile::one;
           
    _sprite.SetSubRect(frame1);
}


void WaterTile::update(int instant)
{
    if(instant==0)
        {
        acc+=Clock.GetElapsedTime();
        //printf("%f \n",acc);
        if(acc>=timer)
        {

            if(currentFrame==WaterTile::one)
            {
                currentFrame=WaterTile::two;
                _sprite.SetSubRect(frame2);
                //printf("FRAME 2!\n");
            }

            else if(currentFrame==WaterTile::two)
            {
                currentFrame=WaterTile::one;
                _sprite.SetSubRect(frame1);
                //printf("FRAME 1!\n");
            }

            _sprite.SetScale(1.0f,1.0f);
            Clock.Reset();
            acc=0;
        }
    }
    
    else
    {
        if(currentFrame==WaterTile::one)
            {
                currentFrame=WaterTile::two;
                _sprite.SetSubRect(frame2);
                
            }

            else if(currentFrame==WaterTile::two)
            {
                currentFrame=WaterTile::one;
                _sprite.SetSubRect(frame1);
                
            }
    }
    
       _sprite.SetScale(2,2);
}

WaterTile::~WaterTile() {
}

sf::Sprite WaterTile::getSprite()
{
    return _sprite;
}

void WaterTile::setPos(float x, float y)
{
    _sprite.SetPosition(x,y);
}