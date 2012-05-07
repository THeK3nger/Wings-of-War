#include "Card.h"

Card::Card(CType type, float mov_x, float mov_y, float mov_theta){
    this->type = type;
    this->dx = mov_x;
    this->dy = mov_y;
    this->dtheta = mov_theta;
}

Card::~Card() {
}

Card::CType Card::getCardType() {
    return this->type;
}

void Card::getMovement(float* outMove) {
    outMove[0] = this->dx;
    outMove[1] = this->dy;
    outMove[2] = this->dtheta;
}
