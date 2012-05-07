/* 
 * File:   Plane.cpp
 * Author: davide
 * 
 * Created on May 7, 2012, 6:44 PM
 */

#include "Plane.h"

Plane::Plane()
{

}

Plane::Plane(const Plane& orig)
{

}

Plane::~Plane()
{

}

void Plane::move(Card card)
{
    if(this->moveIsValid(card))
    {
        float deltas[3];
        
        card.getMovement(deltas);
        
//        this->posx+=deltas[0];
//        this->posy+=deltas[1];
//        this->theta+=deltas[2];
        this->posx = this->posx + deltas[0]*cos(this->theta) - deltas[1]*sin(this->theta);
        this->posy = this->posy + deltas[0]*sin(this->theta) + deltas[1]*cos(this->theta);
        this->theta = this->theta + deltas[2];
    }
}

int Plane::getDamage()
{

}

int Plane::getHealth()
{

}
    
void Plane::setDamage(int value)
{

}
    
void Plane::getPosition(float* thePosition)
{

}
    
int Plane::getLastMove()
{
    
}

bool Plane::moveIsValid(Card card)
{
    
    return true;
}