#include "Card.h"

Card::Card(){
    this->type = STRAIGHT;
    this->dx = 0;
    this->dy = 0;
    this->dtheta = 0;
}

Card::Card(CType type, float mov_x, float mov_y, float mov_theta){
    this->type = type;
    this->dx = mov_x;
    this->dy = mov_y;
    this->dtheta = mov_theta;
}

Card::~Card() {
    std::cout << "Card destructor called\n";
    std::cout.flush();
}

Card::CType Card::getCardType() {
    return this->type;
}

void Card::getMovement(float* outMove) {
    outMove[0] = this->dx;
    outMove[1] = this->dy;
    outMove[2] = this->dtheta;
}

void Card::setMovement(float x, float y, float theta){
    this->dx = x;
    this->dy = y;
    this->dtheta = theta;
}

void Card::setType(CType type){
    this->type = type;
}