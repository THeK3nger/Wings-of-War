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
    
    _spritesheet.LoadFromFile("assets/watertile2.png");
    _sprite.SetImage(_spritesheet);
    
    frame1=sf::IntRect(16,144,48,176);
    frame2=sf::IntRect(74,144,106,176);
    frame3=sf::IntRect(122,144,164,176);
    
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
                printf("frame 1\n");
            }

            else if(currentFrame==WaterTile::two)
            {
                currentFrame=WaterTile::three;
                _sprite.SetSubRect(frame3);
                 printf("frame 2\n");
            }
            
            else if(currentFrame==WaterTile::three)
            {
                currentFrame=WaterTile::one;
                _sprite.SetSubRect(frame1);
                 printf("frame 3\n");
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