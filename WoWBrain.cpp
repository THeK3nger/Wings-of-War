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

CardSet* WoWBrain::nextValidMoves() {   // WARNING: this dinamically allocates memory for a list of cards, remember to destroy it in the caller function
    CardSet *validmoves = new CardSet();
    validmoves->cards_number = 0;
    validmoves->cards = new Card* [this->aiplane->getCardSet()->cards_number]; // prepare to contain the whole set of cards
    
    Plane * plane = this->aiplane;
    
    int count = 0; // will count how many moves are valid
    
    if (aiplane->remainingHealth() <= 0) {
        return validmoves;
    }
    float* positionbuff = new float[3];
    aiplane->getPosition(positionbuff);
    if ((positionbuff[0] < 0) || (positionbuff[0] > current_world->getWidth())){
        delete positionbuff;
        return validmoves;
    }
    if ((positionbuff[1] < 0) || (positionbuff[1] > current_world->getHeight())){
        delete positionbuff;
        return validmoves;
    }
    delete positionbuff;
    
    for (int i = 0; i < plane->getCardSet()->cards_number ; i++){ // for every plane manoeuvre
        if (plane->moveIsValid(plane->getCardSet()->cards[i])){  // if this move is valid
            validmoves->cards[count] = plane->getCardSet()->cards[i];    // add it to the set to return
            count++;    // increase the counter
        }
    }
    
    validmoves->cards_number = count;
    
    return validmoves;
}

CardSet* WoWBrain::returnBestCards(float maxtime) {
//    CardSet* possible_moves = this->aiplane->getCardSet();       // the manoeuvres available to the plane
//                                                                // TODO: substitute it with a call to "nextValidMoves()"
//    
//    Card bestcards[possible_moves.cards_number];   // at most, the best cards will be as much as the plane's possible movements
//    int count = 0;      // this will tell how many "best cards" there are
//    
//    bool maximizing = true;     // will switch between max player and min player ply
    
    // TODO -- Launch the alphaBetaPruningStep() with appropriate initialization (MIN_BETA - MAX_ALPHA, etcetera)
    
    return 0;
}

int WoWBrain::alphaBetaPruningStep(int depth, bool maximizing, CardSet *cardset, int alpha, int beta){
    if (depth == SEARCH_DEPTH)         // leaf node
        return this->computeHeuristic();
    
    
}

int WoWBrain::computeHeuristic(){
    // TODO
    return 1;
}

