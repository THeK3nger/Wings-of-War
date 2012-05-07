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
    outMove[2] = this->dtheta;
}
