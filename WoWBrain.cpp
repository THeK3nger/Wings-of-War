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

CardSet* WoWBrain::nextValidMoves(Plane * plane) {   // WARNING: this dinamically allocates memory for a list of cards, remember to destroy it in the caller function
    CardSet *validmoves = new CardSet();
    validmoves->cards_number = 0;
    validmoves->cards = new Card* [plane->getCardSet()->cards_number]; // prepare to contain the whole set of cards
    
    int count = 0; // will count how many moves are valid
    
    if (plane->remainingHealth() <= 0) {
        return validmoves;
    }
    float* positionbuff = new float[3];
    plane->getPosition(positionbuff);
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

std::vector<CardSequence> WoWBrain::returnBestCards(float maxtime) {
    
    std::vector<CardSequence> best_seq;
    CardSequence cs;
    Plane * opponent;
    std::vector<Plane> * planes = this->current_world->getPlanes();
    
    // look for the opponent
    for (int i = 0; i < planes->size(); i++){
        if((*planes)[i].getId() != this->aiplane->getId()){
            opponent = &((*planes)[i]);
        }
    }
    
    alphaBetaPruningStep(0,true,-MAX_HEURISTIC,MAX_HEURISTIC,&cs,&best_seq,opponent);
    
    return best_seq;
}


// TODO: This is still the "normal" implementation of the algorithm, that is good as long as we have to pick a move, but we will need three, so it must be adapted.
// [I.E. we have to stack the moves, and put them in the "bestmoves" sequences (replacing the "less good" ones) when they reduce the difference between beta and alpha without making it negative... maybe XD]
// TODO: this is still depth based, not time based
int WoWBrain::alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, CardSequence *actual_sequence, std::vector<CardSequence> *best_sequences, Plane * opponent){
    if (depth == SEARCH_DEPTH)         // leaf node
        return this->computeHeuristic();
    
    CardSet * possible_moves;
    
    Card::CType previous_move = this->aiplane->getLastMove();
    
    if(maximizing){     // max player ply (AI PLAYER)
        possible_moves = this->nextValidMoves(this->aiplane);
        for (int i = 0; i < possible_moves->cards_number; i++){
            this->aiplane->move(possible_moves->cards[i]);      // applies a move card
            actual_sequence->cards[depth/2] = possible_moves->cards[i];
            actual_sequence->length = (depth/2) + 1;
            int child_value = this->alphaBetaPruningStep(depth+1, !maximizing, alpha, beta, actual_sequence, best_sequences, opponent);    // recursively calls the alphabeta step on this child
            this->aiplane->revertMove(possible_moves->cards[i]);        // reverts the move
            this->aiplane->setLastMove(previous_move);      // restores the last move
            
            if(child_value >= alpha){           // we add the sequence also for values equal to alpha, because we want more than one choice
                if(child_value > alpha){
                    alpha = child_value;        // update the value
                    if (beta < alpha) break;    // don't add this sequence; "strictly lesser than alpha" because the heuristic value is discrete, hence we want to return more than one optimal move
                    
                    // now must clear the sequences already stored
                    for(int i=0; i<best_sequences->size(); i++){
                        delete &best_sequences[i];
                    }
                    best_sequences->clear();
                }
                
                // now add the new sequence (if it is full length)
                if(depth == SEARCH_DEPTH-1){ // the last MAX layer
                    best_sequences->push_back(*actual_sequence); // COPIES the actual sequence in the 
                }
            }
        }
    }
    else{ // min player ply (OPPONENT)
        possible_moves = this->nextValidMoves(opponent);//
            for (int i = 0; i < possible_moves->cards_number; i++){
                int child_value = this->alphaBetaPruningStep(depth+1, !maximizing, alpha, beta, actual_sequence, best_sequences, opponent);    // recursively calls the alphabeta step on this child
                this->aiplane->revertMove(possible_moves->cards[i]);        // reverts the move
                this->aiplane->setLastMove(previous_move);      // restores the last move
                if (beta > child_value) beta = child_value;
                if (beta < alpha) break;// "strictly lesser than alpha" because the heuristic value is discrete, hence we want to return more than one optimal move
            }
        }
    
    return (maximizing?alpha:beta);
}

int WoWBrain::computeHeuristic(){
    // TODO
    return 1;
}

