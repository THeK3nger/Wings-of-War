#include <math.h>
#include <SFML/System/Clock.hpp>

#include "Animation.h"

Animation::Animation(float xi, float yi, float thetai, float xf, float yf, float thetaf) :
    init_x(xi), init_y(yi), init_theta(thetai),
    final_x(xf), final_y(xf), final_theta(thetaf)
{
    // TODO: compute k according to the given values
    this->k = 50;
    
    // compute coefficients
    this->cx1 = (cos(this->init_theta) + cos(this->final_theta)) * this->k + 2*this->init_x - 2*this->final_x;
    this->cx2 = (-2 * cos(this->init_theta) - cos(this->final_theta)) * this->k - 3*this->init_x + 3*this->final_x;
    this->cx3 = cos(this->init_theta) * this->k;
    
    this->cy1 = (sin(this->init_theta) + sin(this->final_theta)) * this->k + 2*this->init_y - 2*this->final_y;
    this->cy2 = (-2 * sin(this->init_theta) - sin(this->final_theta)) * this->k - 3*this->init_y + 3*this->final_y;
    this->cy3 = sin(this->init_theta) * this->k;
    
    // initialize s
    this->s = 0;
    
    // set step
    this->step = 0.01;
    
    // initialize prev_pos
    this->prev_pos[0] = init_x;
    this->prev_pos[1] = init_y;
}

//Animation::Animation(float* init_pos, Card* card){
//    
//    
//    Animation(init_pos[0],init_pos[1],init_pos[2]);
//}

bool Animation::nextStep(float* pos){
    // has s reached 1? (I.E. is the movement finished?)
    if (s>=1) return false; // s can never be greater than 1, but this adds robustness in case of future changes
    
    if (s == 0){ // this is the first step
        // reset the clock
        this->clock.Reset();
    }
    
    // increase s
    this->s = clock.GetElapsedTime()/ANIMATION_LENGTH;
    if (this->s == 0) this->s = 0.001; // this is to avoid silly orientation of the planes
    if (this->s > 1) this->s = 1; // must not go over the final point;
    
    // compute new x,y coordinates
    pos[0] = pow(this->s, 3) * this->cx1 + pow(this->s, 2) * this->cx2 + this->s * this->cx3 + this->init_x;
    pos[1] = pow(this->s, 3) * this->cy1 + pow(this->s, 2) * this->cy2 + this->s * this->cy3 + this->init_y;
    
    // compute new angle
    pos[2] = -atan2(pos[1]-this->prev_pos[1], pos[0]-this->prev_pos[0]);        // this is MINUS because angles must be considered positive when in the half plane of positive Y
    
    // update prev_pos
    this->prev_pos[0] = pos[0];
    this->prev_pos[1] = pos[1];
    
    return true;
}
