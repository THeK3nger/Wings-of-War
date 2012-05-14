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

int WoWBrain::returnBestCards(float maxtime) {

}

// TODO: this is still depth based, not time based
int WoWBrain::alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, Card *actual_sequence, Card * best_sequence, Plane * opponent){
// TODO-- everything to do again
//    if (depth == SEARCH_DEPTH)         // leaf node
//        return this->computeHeuristic();
//    
//    Card * possible_moves;
//    int possible_moves_number = 0;
//    
//    Card::CType previous_move = this->aiplane->getLastMove();
//    
//    if(maximizing){     // max player ply (AI PLAYER)
//        possible_moves_number = this->nextValidMoves(this->aiplane, possible_moves);
//        for (int i = 0; i < possible_moves_number; i++){
//            this->aiplane->move(&possible_moves[i]);      // applies a move card
//            actual_sequence[depth/2] = &possible_moves[i];
//            int child_value = this->alphaBetaPruningStep(depth+1, !maximizing, alpha, beta, actual_sequence, best_sequences, opponent);    // recursively calls the alphabeta step on this child
//            this->aiplane->revertMove(&possible_moves[i]);        // reverts the move
//            this->aiplane->setLastMove(previous_move);      // restores the last move
//            
//            if(child_value >= alpha){           // we add the sequence also for values equal to alpha, because we want more than one choice
//                if(child_value > alpha){
//                    alpha = child_value;        // update the value
//                    if (beta < alpha) break;    // don't add this sequence; "strictly lesser than alpha" because the heuristic value is discrete, hence we want to return more than one optimal move
//                    
//                    // now must clear the sequences already stored
//                    for(int i=0; i<best_sequences->size(); i++){
//                        delete &best_sequences[i];
//                    }
//                    best_sequences->clear();
//                }
//                
//                // now add the new sequence (if it is full length)
//                if(depth == SEARCH_DEPTH-1){ // the last MAX layer
//                    best_sequences->push_back(*actual_sequence); // COPIES the actual sequence in the 
//                }
//            }
//        }
//    }
//    else{ // min player ply (OPPONENT)
//         possible_moves_number = this->nextValidMoves(opponent, possible_moves);//
//            for (int i = 0; i < possible_moves_number; i++){
//                int child_value = this->alphaBetaPruningStep(depth+1, !maximizing, alpha, beta, actual_sequence, best_sequences, opponent);    // recursively calls the alphabeta step on this child
//                this->aiplane->revertMove(&possible_moves[i]);        // reverts the move
//                this->aiplane->setLastMove(previous_move);      // restores the last move
//                if (beta > child_value) beta = child_value;
//                if (beta < alpha) break;// "strictly lesser than alpha" because the heuristic value is discrete, hence we want to return more than one optimal move
//            }
//        }
//    
//    delete [] possible_moves;
//    
//    return (maximizing?alpha:beta);
}

int WoWBrain::computeHeuristic(){
    // TODO
    return 1;
}

