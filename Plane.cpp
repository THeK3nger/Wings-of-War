#include "Plane.h"

/*!
 * Projects the input angle in the [-π, π] interval
 */
float normalizeAngle(float angle){
    float absangle = (angle > 0? angle : -angle); // absolute value of angle

    // now, bring the angle in the interval [-2pi, 2pi]
    if(absangle>2*M_PI){
        if(angle > 0){ // must decrease the value
            while(angle > 2*M_PI) angle -= 2*M_PI;  // any better idea to do the module operation between two floats?
        }
        else{  // must increase the value
            while(angle < -2*M_PI) angle += 2*M_PI;
        }
    }

    // now, bring the angle in the [-pi, pi] interval
    absangle = (angle > 0? angle : -angle);
    if (absangle > M_PI){
        (angle > 0? angle -= 2*M_PI : angle += 2*M_PI);
    }
    return angle;
}

Plane::Plane(int id, int health, float x, float y, float theta){
    this->id = id;
    this->health = health;
    this->posx = x;
    this->posy = y;
    this->theta = theta;
    this->damage = 0;
    this->lastmove = Card::STRAIGHT;
    
//    for (int i=0; i<cards.size(); i++){
//        this->cards.push_back(cards[i]);
//    }
}

Plane::~Plane()
{

}

void Plane::setCardSet(CardSet *cset){
    this->cardset = cset;
}

CardSet* Plane::getCardSet(){
    return this->cardset;
}

bool Plane::move(Card * card)
{
    if(this->moveIsValid(card))
    {
        float deltas[3];
        
        card->getMovement(deltas);
        
        this->posx = floorf((this->posx + deltas[0]*cos(this->theta) - deltas[1]*sin(this->theta)) * 100 + 0.5)/100;
        this->posy = floorf((this->posy + deltas[0]*sin(this->theta) + deltas[1]*cos(this->theta)) * 100 + 0.5)/100;
        this->theta = this->theta + deltas[2];
        
        this->theta = normalizeAngle(this->theta);
        this->theta = floorf(this->theta * 100 + 0.5)/100;
        
        this->lastmove = card->getCardType();
        
        return true;
    }
    
    return false;
}

void Plane::revertMove(Card * card, Card::CType prev_lastmove){
    float deltas[3];
    card->getMovement(deltas);
    
    this->theta -= deltas[2];
    this->theta = normalizeAngle(this->theta);
    this->theta = floorf(this->theta * 100 + 0.5)/100;
    
    this->posx = floorf((this->posx - deltas[0]*cos(this->theta) + deltas[1]*sin(this->theta)) * 100 + 0.5)/100;
    this->posy = floorf((this->posy - deltas[0]*sin(this->theta) - deltas[1]*cos(this->theta)) * 100 + 0.5)/100;
    
    this->lastmove = prev_lastmove;
}

int Plane::remainingHealth()
{
    return (this->health - this->damage);
}

int Plane::getMaxHealth()
{
    return this->health;
}
    
void Plane::inflictDamage(int amount)
{
    this->damage += amount;
}

void Plane::heal_damage(int amount){
    this->damage -= amount;
}
    
void Plane::getPosition(float* outPosition)
{
    outPosition[0] = this->posx;
    outPosition[1] = this->posy;
    outPosition[2] = this->theta;
}
    
Card::CType Plane::getLastMove()
{
    return this->lastmove;
}

int Plane::getId(){
    return this->id;
}

bool Plane::moveIsValid(Card * card)
{
    // A little experiment: we have 3 cards. They are STRAIGHT, LEFT and RIGHT
    // I'm now forcing a STRAIGHT after each LEFT or RIGHT
    if(card->getCardType() == Card::STRAIGHT) return true;
    if((card->getCardType() == Card::L_STEER) || (card->getCardType() == Card::R_STEER)){
        if(this->lastmove == Card::STRAIGHT) return true;
    }
    return false;
            
    
    // TODO -- will have to adequate the output to the last movement
    // namely:  "normal" manoveurs are always available, except if the last one was an "himmelmann"
    //          "himmelmann" is possible only if last manoveur was "straight"
    //          "straight" is always possible
    //          "dangerous" are possible only if last manoveur was "straight" or "normal"
    return true;
}

bool Plane::canSee(Plane* target){
    float target_pos[3];
    target->getPosition(target_pos);
    
    float diff_x = target_pos[0] - this->posx;
    float diff_y = target_pos[1] - this->posy;
    
    float relative_angle = atan2(diff_y,diff_x) - this->theta;
    if (relative_angle < 0) relative_angle = -relative_angle;   // this takes the absolute value
    if ((relative_angle > SHOOTING_ANGLE) && (relative_angle < 2*M_PI - SHOOTING_ANGLE))    // the plane can shoot when the angle is about 2π (E.G. this plane is oriented at [π-∂], the angle with the enemy is [-π+∂], the difference is [2π-2∂])
        return false;
    
    return true;
}

bool Plane::canShootTo(Plane *target){
    // TODO -- for the moment, we assume that the central points of the two planes must be in the range (in the real game, it is enough to reach ANY part of the card)
    
    // prepare infos
    float target_pos[3];
    target->getPosition(target_pos);
    float diff_x = target_pos[0] - this->posx;
    float diff_y = target_pos[1] - this->posy;
    
    // check distance
    if (pow((diff_x),2) + pow((diff_y),2) > pow(SHOOTING_RADIUS,2))
        return false;
    
    // check angle      --      TODO: I decided not to call the "canSee" method here, so it doesn't have to compute again target_pos, diff_x and diff_y... is it too much?
    float relative_angle = atan2(diff_y,diff_x) - this->theta;
    if (relative_angle < 0) relative_angle = -relative_angle;   // this takes the absolute value
    if ((relative_angle > SHOOTING_ANGLE) && (relative_angle < 2*M_PI - SHOOTING_ANGLE))    // the plane can shoot when the angle is about 2π (E.G. this plane is oriented at [π-∂], the angle with the enemy is [-π+∂], the difference is [2π-2∂])
        return false;

    
    // if the check arrives here, the plane is within both shooting range and shooting angle
    return true; 
}