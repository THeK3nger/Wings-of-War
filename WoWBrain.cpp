/* 
 * File:   WoWBrain.cpp
 * Author: Iron Man, Thor, Hulk
 * 
 * Created on May 7, 2012, 6:46 PM
 */
#include <stdlib.h>

#include "WoWBrain.h"
#include "Plane.h"
#include "World.h"

WoWBrain::WoWBrain(Plane* plane, World * world) {
    this->aiplane = plane;
    this->current_world = world;
    std::vector<Plane *> * planes = this->current_world->getPlanes();
    for (int i = 0; i < planes->size(); i++) {
        if ((*planes)[i]->getId() != this->aiplane->getId()) {
            opponent = (*planes)[i];
            break;
        }
    }
    this->weights = new int[3];
    this->weights[0] = 1; // Distance
    this->weights[1] = 10; // CanShoot? CanSee?
    this->weights[2] = 5; // HitPoint
}

WoWBrain::WoWBrain(const WoWBrain& orig) {
}

WoWBrain::~WoWBrain() {
    delete current_world;
    delete weights;
}

Plane* WoWBrain::getAIPlane() {
    return this->aiplane;
}

void WoWBrain::setWeights(int* weights) {
    this->weights[0] = weights[0]; // Distance
    this->weights[1] = weights[1]; // CanShoot? CanSee?
    this->weights[2] = weights[2]; // HitPoint
}

int WoWBrain::nextValidMoves(Plane * plane, Card** valid_moves) { // WARNING: this dinamically allocates memory for a list of cards, remember to destroy it in the caller function

    if (plane->remainingHealth() <= 0) {
        return 0;
    }
    if (!this->current_world->isInside(plane)) return 0;

    int count = 0; // will count how many moves are valid

    for (int i = 0; i < plane->getCardSet()->cards_number; i++) { // for every plane manoeuvre
        if (plane->moveIsValid(&(plane->getCardSet()->cards[i]))) { // if this move is valid
            valid_moves[count] = (plane->getCardSet()->cards) + i; // add it to the set to return
            count++; // increase the counter
        }
    }

    return count;
}

std::vector<Card *> WoWBrain::returnBestCards(float maxtime) {

    std::vector<Card *> actual_sequence;
    std::vector<Card *> best_sequence;

    alphaBetaPruningStep(0, true, -MAX_HEURISTIC, MAX_HEURISTIC, &actual_sequence, &best_sequence, this->opponent);

    while (best_sequence.size() > CHOICES_PER_TURN) best_sequence.pop_back();

    return best_sequence;
}

// TODO: this is still depth based, not time based

int WoWBrain::alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, std::vector<Card *> * actual_sequence, std::vector<Card *> * best_sequence, Plane * opponent) {
    if (depth == SEARCH_DEPTH) { // leaf node
        int heur = this->computeHeuristic();
        if (heur > beta) return heur;
        if (heur > alpha) {
            best_sequence->clear();
            for (int i = 0; i < actual_sequence->size(); i++) {
                best_sequence->push_back((*actual_sequence)[i]);
            }
        }
        return heur;
    }

    Card ** possible_moves = new Card*[3];
    int possible_moves_number = 0;

    Card::CType previous_move;

    if (maximizing) { // AI PLAYER
        previous_move = this->aiplane->getLastMove();
        possible_moves_number = this->nextValidMoves(this->aiplane, possible_moves);

        if (possible_moves_number == 0) {
            delete possible_moves;
            return -MAX_HEURISTIC;
        }

        int child_value = -MAX_HEURISTIC;

        for (int i = 0; i < possible_moves_number; i++) {
            this->aiplane->move(possible_moves[i]); // applies a move card
            actual_sequence->push_back(possible_moves[i]); // adds this manoeuvre to the actual sequence
            child_value = std::max(child_value, alphaBetaPruningStep(depth + 1, !maximizing, alpha, beta, actual_sequence, best_sequence, opponent));
            this->aiplane->revertMove(possible_moves[i], previous_move);

            if (beta <= child_value) {
                actual_sequence->pop_back();
                delete possible_moves;
                return child_value;
            }

            alpha = std::max(alpha, child_value);

            actual_sequence->pop_back();
        }
    } else { // OPPONENT PLAYER
        previous_move = this->opponent->getLastMove();
        possible_moves_number = this->nextValidMoves(this->opponent, possible_moves);
        if (possible_moves_number == 0) {
            delete possible_moves;
            return MAX_HEURISTIC;
        }
        int child_value = MAX_HEURISTIC;
        bool ai_damaged = false;
        bool opponent_damaged = false;

        for (int i = 0; i < possible_moves_number; i++) {

            this->opponent->move(possible_moves[i]); // applies a move card

            if (aiplane->canShootTo(opponent)) { // if there are damages to be inflicted, inflict them
                opponent_damaged = true;
                opponent->inflictDamage(this->expectedDamage());
            }
            if (opponent->canShootTo(aiplane)) {
                ai_damaged = true;
                aiplane->inflictDamage(this->expectedDamage());
            }

            child_value = std::min(child_value, alphaBetaPruningStep(depth + 1, !maximizing, alpha, beta, actual_sequence, best_sequence, opponent)); // recursive call on the child

            // now restore previous state
            this->opponent->revertMove(possible_moves[i], previous_move); // reverts the move

            if (opponent_damaged) opponent->heal_damage(this->expectedDamage()); // restores the damages
            if (ai_damaged) aiplane->heal_damage(this->expectedDamage());

            if (child_value <= alpha) {
                delete possible_moves;
                return child_value;
            }

            beta = std::min(beta, child_value);
        }
    }

    delete possible_moves;
    return (maximizing ? alpha : beta);
}

int WoWBrain::computeHeuristic() {
    // How this heuristic works?
    //
    // Heuristic function H(s) is defined as
    //
    // H(s) = Score(AI,s) - Score(Opponent,s)
    //
    // where
    //
    // Score(X,s) = w1*ShotValue(X,s) + w2*RemainingLife(X,s)
    //
    // ShotValue is a function that can assume the following values:
    //          * 0 if Plane X CANNOT see Y
    //          * 1 if Plane X can see Y but CANNOT shoot it (out of range)
    //          * 2 if Plane X can see and shoot on Y
    //
    // RamainingLife, instead, is just the amount of remaining life points
    // of the Plane X.
    //
    if (this->aiplane->remainingHealth() <= 0) {
        return -MAX_HEURISTIC;
    }

    if (this->opponent->remainingHealth() <= 0) {
        return MAX_HEURISTIC;
    }

    float aipos[3];
    float opponentpos[3];
    this->aiplane->getPosition(aipos);
    this->opponent->getPosition(opponentpos);

    // Compute Manhattan Distance
    // I don't use this for now. It's a tricky part...
    //int manhattan = (int) abs(aipos[0] - opponentpos[0]);
    //manhattan += (int) abs(aipos[1] - opponentpos[1]);

    // Compute ShotValue
    int aivalue = 0;
    int opponentvalue = 0;

    if (aiplane->canSee(opponent)) {
        aivalue++;
    }
    if (opponent->canSee(aiplane)) {
        opponentvalue++;
    }
    if (aiplane->canShootTo(opponent)) {
        aivalue++;
    }
    if (opponent->canShootTo(aiplane)) {
        opponentvalue++;
    }

    int aiscore = weights[1] * aivalue + weights[2]*(aiplane->remainingHealth());
    int opponentscore = weights[1] * opponentvalue + weights[2]*(opponent->remainingHealth());

    return aiscore - opponentscore;
}

int WoWBrain::expectedDamage() {
    return 1;
}