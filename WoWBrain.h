/* 
 * File:   WoWBrain.h
 * Author: Iron Man, Thor, Hulk
 *
 * Created on May 7, 2012, 6:46 PM
 */

#ifndef WOWBRAIN_H
#define	WOWBRAIN_H
#define SEARCH_DEPTH 4
#define CHOICES_PER_TURN 1
#define MAX_HEURISTIC 1000

#include "Plane.h"
#include "World.h"
#include "Card.h"
#include <vector>

class WoWBrain {
public:
    WoWBrain(Plane* plane);
    WoWBrain(const WoWBrain& orig);
    virtual ~WoWBrain();
    
    //DRAFT: All this functions are just a preliminary draft.
    
    /*!
     * Return ID of AI-controlled Plane.
     * 
     * \return The ID of AI-controlled Plane.
     */
    Plane* getAIPlane();
    
    /*!
     * Ask to AI for the best available move given the current status.
     * 
     * Implemented with Iterative-Deepening-Search with Alpha-Beta Pruning.
     * 
     * \param maxtime Time limit (NOW UNUSED).
     * \return A pointer to the best available move. (FUTURE: best 3-moves).
     */
    int returnBestCards(float maxtime); 
    
    /*!
     * Return a pointer to a list of Cards representing all the possible
     * moves available to the given plane in the current state.
     * \param plane A pointer to the Plane to analyze
     */
    int nextValidMoves(Plane * plane, Card* valid_moves); // this needs a plane as input because we want to compute the next possible moves of either the AI plane and the opponent plane
    
    /*!
     * Computes the heuristic based o the actual world state
     */
    int computeHeuristic();
    
private:
    
    /*!
     * Implements the alphaBetaPruning algorithm
     * \param depth the reached depth
     */
    int alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, CardSequence *actual_sequence, std::vector<CardSequence> *sequences, Plane * opponent);
    
    World* current_world;
    Plane* aiplane;

};

#endif	/* WOWBRAIN_H */

