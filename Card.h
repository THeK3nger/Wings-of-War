/* 
 * File:   Card.h
 * Author: davide
 *
 * Created on May 7, 2012, 6:44 PM
 */

#ifndef CARD_H
#define	CARD_H

class Card {
public:
    enum CType {
        STRAIGHT,
        R_STEER,
        L_STEER,
    };
    
    Card();
    Card(const Card& orig);
    virtual ~Card();
private:
    float dx;
    float dy;
    float theta;
    CType type;
    
    void getMovement(float* outMove);
    CType getCardType();    

};

#endif	/* CARD_H */

