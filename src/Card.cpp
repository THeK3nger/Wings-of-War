#include "Card.h"

Card::Card() :
    type(STRAIGHT), dx(0), dy(0), dtheta(0)
{}

Card::Card(CType type, float mov_x, float mov_y, float mov_theta) :
    type(type), dx(mov_x), dy(mov_y), dtheta(mov_theta)
{}

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

void Card::setMovement(float x, float y, float theta) {
    this->dx = x;
    this->dy = y;
    this->dtheta = theta;
}

void Card::setType(CType type) {
    this->type = type;
}
