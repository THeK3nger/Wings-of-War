/* 
 * File:   CardImage.h
 * Author: malcom
 *
 * Created on May 26, 2012, 11:13 AM
 */

#ifndef CARDIMAGE_H
#define	CARDIMAGE_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "badge.h"

#define ACTIVATION_OFFSET 50
#define SCALE 0.5f

class CardImage {
public:
    CardImage(int theId,float xpos, float ypos,sf::RenderWindow *refwindow);
    virtual ~CardImage();
    
    int getId();
    void activateCard();
    void deActivateCard();
    void setPos(sf::Vector2f pos);
    void getPos();
    
    void draw();
    
    sf::Sprite cardSprite;
    bool activated;
    
private:

    sf::Image _cardImage;
    sf::String _cardName;
    sf::RenderWindow* _window;
    
    badge* _badge;
    
    int _id;
    
    

};

#endif	/* CARDIMAGE_H */

