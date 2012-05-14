/* 
 * File:   WoWBrain.cpp
 * Author: Iron Man, Thor, Hulk
 * 
 * Created on May 7, 2012, 6:46 PM
 */

#include "WoWBrain.h"
#include "Plane.h"
#include "World.h"

WoWBrain::WoWBrain(Plane* plane, World * world) {
    this->aiplane = plane;
    this->current_world = world;
    std::vector<Plane *> * planes = this->current_world->getPlanes();
    for(int i=0; i<planes->size();i++){
        if ((*planes)[i]->getId() != this->aiplane->getId()){
            opponent = (*planes)[i];
            break;
        }
    }
}

WoWBrain::WoWBrain(const WoWBrain& orig) {
}

WoWBrain::~WoWBrain() {
    delete current_world;
}

Plane* WoWBrain::getAIPlane() {
    return this->aiplane;
}

int WoWBrain::nextValidMoves(Plane * plane, Card* valid_moves) {   // WARNING: this dinamically allocates memory for a list of cards, remember to destroy it in the caller function
    
    valid_moves = new Card [plane->getCardSet()->cards_number];
    
    int count = 0; // will count how many moves are valid
    
    if (plane->remainingHealth() <= 0) {
        return 0;
    }
    float* positionbuff = new float[3];
    plane->getPosition(positionbuff);
    if ((positionbuff[0] < 0) || (positionbuff[0] > current_world->getWidth())){
        delete positionbuff;
        return 0;
    }
    if ((positionbuff[1] < 0) || (positionbuff[1] > current_world->getHeight())){
        delete positionbuff;
        return 0;
    }
    delete positionbuff;
    
    for (int i = 0; i < plane->getCardSet()->cards_number ; i++){ // for every plane manoeuvre
        if (plane->moveIsValid(&(plane->getCardSet()->cards[i]))){  // if this move is valid
            valid_moves[count] = plane->getCardSet()->cards[i];    // add it to the set to return
            count++;    // increase the counter
        }
    }
    
    return count+1;
}

std::vector<Card *> WoWBrain::returnBestCards(float maxtime) {

    std::vector<Card *> actual_sequence;
    std::vector<Card *> best_sequence;
    
    alphaBetaPruningStep(0, true, -MAX_HEURISTIC, MAX_HEURISTIC, &actual_sequence, &best_sequence, this->opponent);
    
    while(best_sequence.size() > CHOICES_PER_TURN) best_sequence.pop_back();
    
    return best_sequence;
}

// TODO: this is still depth based, not time based
int WoWBrain::alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, std::vector<Card *> * actual_sequence, std::vector<Card *> * best_sequence, Plane * opponent){
    if(depth == SEARCH_DEPTH)   // leaf node
        return this->computeHeuristic();
    
    Card * possible_moves;
    int possible_moves_number = 0;
    
    Card::CType previous_move;
    
    if(maximizing){     // AI PLAYER
        previous_move = this->aiplane->getLastMove();
        possible_moves_number = this->nextValidMoves(this->aiplane,possible_moves);
        
        int child_value = -MAX_HEURISTIC;
        
        for (int i = 0; i < possible_moves_number; i++){
            this->aiplane->move(&possible_moves[i]);      // applies a move card
            actual_sequence->push_back(&possible_moves[i]);     // adds this manoeuvre to the actual sequence
            child_value = alphaBetaPruningStep(depth+1,!maximizing,alpha,beta,actual_sequence,best_sequence,opponent);
            this->aiplane->revertMove(&possible_moves[i], previous_move);
            
            if(child_value > alpha){
                alpha = child_value;
                if (beta <= alpha) {actual_sequence->pop_back();break;}    // don't add this sequence
                
                best_sequence->clear();
                for(int i=0; i<actual_sequence->size(); i++){
                    best_sequence->push_back((*actual_sequence)[i]);
                }
            }
            
            actual_sequence->pop_back();
        }
    }
    else{       // OPPONENT PLAYER
        previous_move = this->opponent->getLastMove();
        possible_moves_number = this->nextValidMoves(this->opponent,possible_moves);
        for (int i = 0; i < possible_moves_number; i++){
            this->opponent->move(&possible_moves[i]);      // applies a move card
            int child_value = alphaBetaPruningStep(depth+1,!maximizing,alpha,beta,actual_sequence,best_sequence,opponent);
            this->opponent->revertMove(&possible_moves[i], previous_move);
            
            if(child_value < beta){
                beta = child_value;
                if (beta <= alpha) break;    // don't add this sequence
            }
        }
    }
    
    delete [] possible_moves;
    
    return (maximizing?alpha:beta);
}

int WoWBrain::computeHeuristic(){
    // TODO: Just an example....
    float* tmp_pos = new float[3];
    this->aiplane->getPosition(tmp_pos);
    float y = tmp_pos[1];
    delete tmp_pos;
    return (int) (y+0.5);
}

