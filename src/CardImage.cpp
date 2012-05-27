/* 
 * File:   CardImage.cpp
 * Author: malcom
 * 
 * Created on May 26, 2012, 11:13 AM
 */

#include "CardImage.h"

CardImage::CardImage(int theId,float xpos, float ypos)
{
    _id=theId;
    _cardImage.LoadFromFile("assets/bluecard.png");
    cardSprite.SetImage(_cardImage);
    cardSprite.SetPosition(xpos,ypos);
    cardSprite.SetScale(SCALE,SCALE);
    activated=0;
}

CardImage::~CardImage() {
}

int CardImage::getId()
{
    return _id;
}

void CardImage::activateCard()
{
    if(activated==0)
    {
    sf::Vector2f pos;
    pos=cardSprite.GetPosition();
    pos.y=pos.y-ACTIVATION_OFFSET;
    cardSprite.SetPosition(pos);
    activated=1;
    }
    
}
void CardImage::deActivateCard()
{
    if(activated==1)
    {
    sf::Vector2f pos;
    pos=cardSprite.GetPosition();
    pos.y+=ACTIVATION_OFFSET;
    cardSprite.SetPosition(pos);
    activated=0;
    }
}
void CardImage::setPos(sf::Vector2f pos)
{
    cardSprite.SetPosition(pos);
}
void CardImage::getPos()
{
   
}