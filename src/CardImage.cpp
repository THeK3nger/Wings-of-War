
#include "CardImage.h"
#include "Game.h"
#include "resources/ResourcesManager.h"
#include "resources/ImageRes.h"

std::string CardsFile[6]={
        "card_right_long",
        "card_left_long",
        "card_straight_long",
        "card_right_short",
        "card_left_short",
        "card_straight_short"
};

CardImage::CardImage(int theId,float xpos, float ypos,std::map<int,int>* cardmaster,int file) :
    _window(Game::getMainWindow())
{
    _id=theId;
    _cardImage = GET_SFML_IMAGE_FROM_MANAGER(CardsFile[file]);
    cardSprite.SetImage(_cardImage);
    cardSprite.SetPosition(xpos,ypos);
    cardSprite.SetScale(SCALE,SCALE);
    activated=0;
    
    _cardmaster=cardmaster;
    _timer=0;
    anim=0;
    
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
    _window.Draw(cardSprite);
}

void CardImage::update()
{

	if(anim==0)
	{
		_Clock.Reset();
	}
	else
	{
		_timer=_Clock.GetElapsedTime();
		cardSprite.SetColor(sf::Color::Red);
		if(_timer==1.0f)
		{
			anim=0;
			cardSprite.SetColor(sf::Color(0,0,0,0));
		}
	}

}
