/* 
 * File:   Card.cpp
 * Author: davide
 * 
 * Created on May 7, 2012, 6:44 PM
 */

#include "Card.h"

Card::Card() {
}

Card::Card(const Card& orig) {
}

Card::~Card() {
}

Card::CType Card::getCardType() {
    return this->type;
}

void Card::getMovement(float* outMove) {
    outMove[0] = this->dx;
    outMove[1] = this->dy;
    outMove[2] = this->theta;
}
