#ifndef WOWBRAIN_H
#define	WOWBRAIN_H

#include "Plane.h"
#include "World.h"
#include "Card.h"
#include <limits.h>
#include <vector>

//#define SEARCH_DEPTH 14 // must be an EVEN number
#define CHOICES_PER_TURN 2 // can be at most 1/2 * SEARCH_DEPTH
#define MAX_HEURISTIC 1000000
#define MIN_HEURISTIC (-1000000)
#define MAX_THINK_TIME 10 // seconds limit for the AI to choose a move

class Sequence{
	bool cards_initialized;
public:
	std::vector<Card*> *cards;
	int heuristic_value;

	Sequence();
	Sequence(Sequence * to_be_copied);
	~Sequence();
	void initCards();
	bool cardsExist();
	void copy(Sequence * to_be_copied);
	void print();
};

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
     * Return ID of Opponent Plane.
     * 
     * \return The ID of Opponent Plane.
     */
    Plane* getOpponentPlane();
    
    /*!
     * Ask to AI for the best available move given the current status.
     * 
     * Implemented with Iterative-Deepening-Search with Alpha-Beta Pruning.
     * 
     * \param howmany number of cards that must be returned
     * 
     * \return A pointer to the best available move. (FUTURE: best 3-moves).
     */

    std::vector<Card *> returnBestCards();

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
    
    /*!
     * Returns the expected value for the damage due to a shot
     * TODO: maybe this will take as input a "DamageSet", or better a Plane. IDEA: store the expected value for each in the constructor, so that it is ready when needed
     */
    int expectedDamage();
    
    void setWeights(int* _weights);

private:

    /*!
     * \brief chooses a moves sequence just to stay inside the field
     */
    bool chooseSafeSequence(std::vector<Card *> * seq, int next_move_to_try);

    /*!
     * Implements the alphaBetaPruning algorithm
     * \param depth the reached depth
     * \return True if in choice has been put a valid Sequence
     */
    int alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, std::vector<Card *> * actual_sequence, Card** &choice, int &choice_lenght);

    World *_current_world;
    Plane *_aiplane;
    Plane *_opponent;
    int* _weights;

};

#endif	/* WOWBRAIN_H */

