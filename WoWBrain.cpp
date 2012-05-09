/* 
 * File:   WoWBrain.cpp
 * Author: Iron Man, Thor, Hulk
 * 
 * Created on May 7, 2012, 6:46 PM
 */

#include "WoWBrain.h"
#include "Plane.h"
#include "World.h"

WoWBrain::WoWBrain(Plane* plane) {
    this->aiplane = plane;
}

WoWBrain::WoWBrain(const WoWBrain& orig) {
}

WoWBrain::~WoWBrain() {
}

Plane* WoWBrain::getAIPlane() {
    return this->aiplane;
}

Card* WoWBrain::nextValidMoves() {
    if (aiplane->remainingHealth() <= 0) {
        return 0;
    }
    float* positionbuff = new float[3];
    aiplane->getPosition(positionbuff);
    if ((positionbuff[0] < 0) || (positionbuff[0] > current_world->getWidth()))
        return 0;
    if ((positionbuff[1] < 0) || (positionbuff[1] > current_world->getHeight()))
        return 0;
    // TODO: Continue with valid code.
    return 0;
}

Card* WoWBrain::returnBestCards(float maxtime) {
    return 0;
}

