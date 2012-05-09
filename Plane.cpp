#include "Plane.h"


#include <vector>

Plane::Plane(int id, int health, float x, float y, float theta, std::vector<Card> cards){
    this->id = id;
    this->health = health;
    this->posx = x;
    this->posy = y;
    this->theta = theta;
    this->damage = 0;
    
    for (int i=0; i<cards.size(); i++){
        this->cards.push_back(cards[i]);
    }
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
        
        float abstheta = (this->theta > 0? this->theta : -this->theta); // absolute value of theta
        
        // now, bring the angle in the interval [-2pi, 2pi]
        if(abstheta>2*M_PI){
            if(this->theta > 0){ // must decrease the value
                while(this->theta > 2*M_PI) this->theta -= 2*M_PI;  // any better idea to do the module operation between two floats?
            }
            else{  // must increase the value
                while(this->theta < -2*M_PI) this->theta += 2*M_PI;
            }
        }
        
        // now, bring the angle in the [-pi, pi] interval
        abstheta = (this->theta > 0? this->theta : -this->theta);
        if (abstheta > M_PI){
            (this->theta > 0? this->theta -= 2*M_PI : this->theta += 2*M_PI);
        }
    }
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
    
void Plane::getPosition(float* outPosition)
{
    outPosition[0] = this->posx;
    outPosition[1] = this->posy;
    outPosition[2] = this->theta;
}
    
int Plane::getLastMove()
{
    return this->lastmove;
}

int Plane::getId(){
    return this->id;
}

bool Plane::moveIsValid(Card card)
{
    // TODO -- will have to adequate the output to the last movement
    // namely:  "normal" manoveurs are always available, except if the last one was an "himmelmann"
    //          "himmelmann" is possible only if last manoveur was "straight"
    //          "straight" is always possible
    //          "dangerous" are possible only if last manoveur was "straight" or "normal"
    return true;
}

bool Plane::canShootTo(Plane target){
    // TODO -- for the moment, we assume that the central points of the two planes must be in the range (in the real game, it is enough to reach ANY part of the card)
    
    // prepare infos
    float target_pos[3];
    target.getPosition(target_pos);
    float diff_x = this->posx - target_pos[0];
    float diff_y = this->posy - target_pos[1];
    
    // check distance
    if (pow((diff_x),2) + pow((diff_y),2) > pow(SHOOTING_RADIUS,2))
        return false;
    
    // check angle
    float relative_angle = atan2(diff_y,diff_x) - this->theta;
    if (relative_angle < 0) relative_angle = -relative_angle;   // this takes the absolute value
    if ((relative_angle > SHOOTING_ANGLE) && (relative_angle < 2*M_PI - SHOOTING_ANGLE))    // the plane can shoot when the angle is about 2π (E.G. this plane is oriented at [π-∂], the angle with the enemy is [-π+∂], the difference is [2π-2∂])
        return false;
    
    // if the check arrives here, the plane is within both shooting range and shooting angle
    return true; 
}