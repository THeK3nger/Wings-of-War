/* 
 * File:   CardImage.cpp
 * Author: malcom
 * 
 * Created on May 26, 2012, 11:13 AM
 */

#include "CardImage.h"

std::string CardsFile[6]={	"assets/arrows/left_long.png",
							"assets/arrows/left_short.png",
							"assets/arrows/right_long.png",
							"assets/arrows/right_short.png",
							"assets/arrows/straight_long.png",
							"assets/arrows/straight_short.png"};



CardImage::CardImage(int theId,float xpos, float ypos,sf::RenderWindow *refwindow,std::map<int,int>* cardmaster,int file)
{
    _id=theId;
    _cardImage.LoadFromFile(CardsFile[file]);
    cardSprite.SetImage(_cardImage);
    cardSprite.SetPosition(xpos,ypos);
    cardSprite.SetScale(SCALE,SCALE);
    activated=0;
    
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
}
