/* 
 * File:   WaterTile.cpp
 * Author: malcom
 * 
 * Created on May 19, 2012, 12:57 PM
 */

#include "WaterTile.h"
#include "Game.h"
#include "resources/ResourcesManager.h"
#include "resources/ImageRes.h"

WaterTile::WaterTile() :
    _window(Game::getMainWindow()), _frame_step(20), _frame_count(0)
{
    
    xpos=100;
    ypos=100;
    
    _spritesheet = GET_SFML_IMAGE_FROM_MANAGER("watertile");
    _sprite.SetImage(_spritesheet);
    
    frame1=sf::IntRect(16,144,48,176);
    frame2=sf::IntRect(74,144,106,176);
    frame3=sf::IntRect(122,144,154,176);
    
    currentFrame=WaterTile::one;
           
    _sprite.SetSubRect(frame1);
}


void WaterTile::update()
{
    if (_frame_count==_frame_step) {
        switch (this->currentFrame) {

        case WaterTile::one :
            currentFrame=WaterTile::two;
            _sprite.SetSubRect(frame2);
            break;
        case WaterTile::two :
            currentFrame=WaterTile::three;
            _sprite.SetSubRect(frame3);
            break;
        case WaterTile::three :
            currentFrame=WaterTile::one;
            _sprite.SetSubRect(frame1);
        }
        _frame_count = 0;
    }
    //_sprite.SetScale(1.0f,1.0f);
    _sprite.SetScale(2,2);
    _frame_count++;
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
