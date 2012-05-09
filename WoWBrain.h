/* 
 * File:   WoWBrain.h
 * Author: Iron Man, Thor, Hulk
 *
 * Created on May 7, 2012, 6:46 PM
 */

#ifndef WOWBRAIN_H
#define	WOWBRAIN_H

#include "Plane.h"
#include "World.h"
#include "Card.h"

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
    int getAIPlane();
    
    /*!
     * Ask to AI for the best available move given the current status.
     * 
     * Implemented with Iterative-Deepening-Search with Alpha-Beta Pruning.
     * 
     * \param maxtime Time limit (NOW UNUSED).
     * \return A pointer to the best available move. (FUTURE: best 3-moves).
     */
    Card* returnBestCards(float maxtime);    
    
    /*!
     * Return a pointer to a list of Cards representing all the possible
     * moves available in the current state.
     */
    Card* nextValidMoves();
    
private:
    
    World* current_world;
    Plane* aiplane;

};

#endif	/* WOWBRAIN_H */

