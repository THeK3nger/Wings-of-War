#ifndef CARDIMAGE_H
#define	CARDIMAGE_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <stdio.h>
#include <stdlib.h>


#define ACTIVATION_OFFSET 50
#define SCALE 0.6f



class CardImage {
public:
    CardImage(int theId, float xpos, float ypos, std::map<int,int>* cardmaster, int file=0);
    virtual ~CardImage();
    
    int getId();
    void activateCard();
    void deActivateCard();
    void setPos(sf::Vector2f pos);
    void getPos();
    void update();
    void draw();
    

    bool anim;
    sf::Sprite cardSprite;
    bool activated;

    sf::Rect<int>* clickableArea;
    
private:

    sf::Image _cardImage;
    sf::String _cardName;
    sf::RenderWindow& _window;
    
    int _id;
    float _timer;
    sf::Clock _Clock;

    std::map<int,int>* _cardmaster;

};

#endif	/* CARDIMAGE_H */

