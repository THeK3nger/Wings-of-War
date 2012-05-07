/* 
 * File:   Plane.h
 * Author: davide
 *
 * Created on May 7, 2012, 6:44 PM
 */
#ifndef PLANE_H
#define	PLANE_H

#include "Card.h"
#include <math.h>

class Plane {
public:
    
    Plane();
    Plane(const Plane& orig);
    virtual ~Plane();
    
    void move(Card card);
    int getDamage();
    int getHealth();
    
    void setDamage(int value);
    
    void getPosition(float* thePosition);
    
    int getLastMove();
    
    bool moveIsValid(Card card);
    
private:
       
    float posx;
    float posy;
    float theta;
    
    int id;
    
    int damage;
    int health;
    Card::CType lastmove;
    
};

#endif	/* PLANE_H */

