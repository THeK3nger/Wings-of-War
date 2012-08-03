/* 
 * File:   CardImage.cpp
 * Author: malcom
 * 
 * Created on May 26, 2012, 11:13 AM
 */

#include "CardImage.h"

CardImage::CardImage(int theId,float xpos, float ypos,sf::RenderWindow *refwindow,std::map<int,int>* cardmaster)
{
    _id=theId;
    _cardImage.LoadFromFile("assets/bluecard.png");
    cardSprite.SetImage(_cardImage);
    cardSprite.SetPosition(xpos,ypos);
    cardSprite.SetScale(SCALE,SCALE);
    activated=0;
    
    _badge = new badge(refwindow,xpos+10,ypos-ACTIVATION_OFFSET);
    
    _window=refwindow;
    _cardmaster=cardmaster;
    
    
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
   
    std::map<int,int>::iterator it;
    it=_cardmaster->find(this->_id);
    
    char buffer[33];
    sprintf(buffer, "%d",it->second);
    _badge->setText(buffer);
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

void CardImage::draw()
{
    _window->Draw(cardSprite);
    if(activated)
    _badge->draw();
}