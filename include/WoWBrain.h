#ifndef WOWBRAIN_H
#define	WOWBRAIN_H

#include "Plane.h"
#include "World.h"
#include "Card.h"
#include <limits.h>
#include <vector>

#define SEARCH_DEPTH 6 // must be an EVEN number
#define CHOICES_PER_TURN 2 // can be at most 1/2 * SEARCH_DEPTH
#define MAX_HEURISTIC INT_MAX

class WoWBrain {
public:
    WoWBrain(Plane* plane, World * world);
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
    std::vector<Card *> returnBestCards(float maxtime);

    /*!
     * Return a pointer to a list of Cards representing all the possible
     * moves available to the given plane in the current state.
     * \param plane A pointer to the Plane to analyze
     */
    int nextValidMoves(Plane * plane, Card** valid_moves); // this needs a plane as input because we want to compute the next possible moves of either the AI plane and the opponent plane

    /*!
     * Computes the heuristic based o the actual world state
     */
    int computeHeuristic();

    void setWeights(int* weights);

private:

    /*!
     * Implements the alphaBetaPruning algorithm
     * \param depth the reached depth
     */
    int alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, std::vector<Card *> * actual_sequence, std::vector<Card *> * best_sequence, Plane * opponent);

    /*!
     * Returns the expected value for the damage due to a shot
     * TODO: maybe this will take as input a "DamageSet", or better a Plane. IDEA: store the expected value for each in the constructor, so that it is ready when needed
     */
    int expectedDamage();

    World *current_world;
    Plane *aiplane;
    Plane *opponent;
    int* weights;

};

#endif	/* WOWBRAIN_H */

