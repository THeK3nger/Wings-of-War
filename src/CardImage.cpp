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
}

CardImage::~CardImage() {
}

int CardImage::getId()
{
    return _id;
}
void CardImage::activateCard()
{
    sf::Vector2f pos;
    pos=cardSprite.GetPosition();
    pos.y+=ACTIVATION_OFFSET;
    cardSprite.SetPosition(pos);
}
void CardImage::deActivateCard()
{
    sf::Vector2f pos;
    pos=cardSprite.GetPosition();
    pos.y-=ACTIVATION_OFFSET;
    cardSprite.SetPosition(pos);
}
void CardImage::setPos(sf::Vector2f pos)
{
    cardSprite.SetPosition(pos);
}
void CardImage::getPos()
{
   
}