#include <stdlib.h>

#include "WoWBrain.h"
#include "Plane.h"
#include "World.h"
#include "Game.h"

WoWBrain::WoWBrain(Plane* plane, World * world) :
_aiplane(plane), _current_world(world)
{
	std::vector<Plane *> * planes = this->_current_world->getPlanes();
	for (int i = 0; i < planes->size(); i++) {
		if ((*planes)[i]->getId() != this->_aiplane->getId()) {
			_opponent = (*planes)[i];
			break;
		}
	}
	this->_weights = new int[3];
	/*
    this->_weights[0] = 1; // Distance
    this->_weights[1] = 10; // CanShoot? CanSee?
    this->_weights[2] = 5; // HitPoint
	 */
	this->_weights[0] = Game::conf.E_distance;
	this->_weights[1] = Game::conf.E_visibility;
	this->_weights[2] = Game::conf.E_health;

}

WoWBrain::WoWBrain(const WoWBrain& orig) {
}

WoWBrain::~WoWBrain() {
	delete _current_world;
	delete _weights;
}

Plane* WoWBrain::getAIPlane() {
	return this->_aiplane;
}

Plane* WoWBrain::getOpponentPlane(){
	return this->_opponent;
}

void WoWBrain::setWeights(int* weights) {
	this->_weights[0] = weights[0]; // Distance
	this->_weights[1] = weights[1]; // CanShoot? CanSee?
	this->_weights[2] = weights[2]; // HitPoint
}

int WoWBrain::nextValidMoves(Plane * plane, Card** valid_moves) { // WARNING: this dinamically allocates memory for a list of cards, remember to destroy it in the caller function

	if (plane->remainingHealth() <= 0) {
		return 0;
	}
	if (!this->_current_world->isInside(plane)) return 0;

	int count = 0; // will count how many moves are valid

	for (int i = 0; i < plane->getCardSet()->cards_number; i++) { // for every plane manoeuvre
		if (plane->moveIsValid(&(plane->getCardSet()->cards[i]))) { // if this move is valid
			valid_moves[count] = (plane->getCardSet()->cards) + i; // add it to the set to return
			count++; // increase the counter
		}
	}

	return count;
}

std::vector<Card *> WoWBrain::returnBestCards(int howmany, float maxtime) {

	std::vector<Card *> actual_sequence;
	std::vector<Card *> best_sequence;

	// TODO: this should use the "maxtime" given

	int alpha = -MAX_HEURISTIC;
	int beta = MAX_HEURISTIC;

	int best_heur = alphaBetaPruningStep(0, true, alpha, beta, &actual_sequence, &best_sequence, this->_opponent);
	std::cout << "THE BEST HEURISTIC IS: " << best_heur << std::endl;

	while (best_sequence.size() > howmany) best_sequence.pop_back();

	return best_sequence;
}

// TODO: this is still depth based, not time based

int WoWBrain::alphaBetaPruningStep(int depth, bool maximizing, int &alpha, int &beta, std::vector<Card *> * actual_sequence, std::vector<Card *> * best_sequence, Plane * opponent) {
	if (depth == Game::conf.search_depth) { // leaf node
		int heur = this->computeHeuristic();
		if (heur > beta) return heur;
		if (heur > alpha) {
			best_sequence->clear();
			for (int i = 0; i < actual_sequence->size(); i++) {
				best_sequence->push_back((*actual_sequence)[i]);
			}
			std::cout << "best heuristic: " << heur << std::endl;
			alpha = heur;
		}
		return heur;
	}

	Card ** possible_moves;
	int possible_moves_number = 0;

	Card::CType previous_move;

	if (maximizing) { // AI PLAYER
		possible_moves = new Card*[_aiplane->getCardSet()->cards_number];
		previous_move = this->_aiplane->getLastMove();
		possible_moves_number = this->nextValidMoves(this->_aiplane, possible_moves);

		if (possible_moves_number == 0) {
			delete[] possible_moves;
			return -MAX_HEURISTIC;
		}

		int child_value = -MAX_HEURISTIC;

		for (int i = 0; i < possible_moves_number; i++) {
			float restore_pos[3];
			this->_aiplane->getPosition(restore_pos);
			this->_aiplane->move(possible_moves[i]); // applies a move card
			actual_sequence->push_back(possible_moves[i]); // adds this manoeuvre to the actual sequence
			child_value = std::max(child_value, alphaBetaPruningStep(depth + 1, !maximizing, alpha, beta, actual_sequence, best_sequence, opponent));
			//            this->_aiplane->revertMove(possible_moves[i], previous_move);
			this->_aiplane->setX(restore_pos[0]);
			this->_aiplane->setY(restore_pos[1]);
			this->_aiplane->setT(restore_pos[2]);

			if (beta <= child_value) {
				actual_sequence->pop_back();
				delete[] possible_moves;
				return child_value;
			}

			alpha = std::max(alpha, child_value);

			actual_sequence->pop_back();
		}
	} else { // OPPONENT PLAYER
		possible_moves = new Card*[_opponent->getCardSet()->cards_number];
		previous_move = this->_opponent->getLastMove();
		possible_moves_number = this->nextValidMoves(this->_opponent, possible_moves);
		if (possible_moves_number == 0) {
			delete[] possible_moves;
			return MAX_HEURISTIC;
		}
		int child_value = MAX_HEURISTIC;
		bool ai_damaged = false;
		bool opponent_damaged = false;

		for (int i = 0; i < possible_moves_number; i++) {
			ai_damaged = false;
			opponent_damaged = false;

			float restore_pos[3];
			this->_opponent->getPosition(restore_pos);

			this->_opponent->move(possible_moves[i]); // applies a move card

			if (_aiplane->canShootTo(opponent)) { // if there are damages to be inflicted, inflict them
				opponent_damaged = true;
				opponent->inflictDamage(this->expectedDamage());
			}
			if (opponent->canShootTo(_aiplane)) {
				ai_damaged = true;
				_aiplane->inflictDamage(this->expectedDamage());
			}

			child_value = std::min(child_value, alphaBetaPruningStep(depth + 1, !maximizing, alpha, beta, actual_sequence, best_sequence, opponent)); // recursive call on the child

			// now restore previous state
			//            this->_opponent->revertMove(possible_moves[i], previous_move); // reverts the move
			this->_opponent->setX(restore_pos[0]);
			this->_opponent->setY(restore_pos[1]);
			this->_opponent->setT(restore_pos[2]);

			if (opponent_damaged) opponent->heal_damage(this->expectedDamage()); // restores the damages
			if (ai_damaged) _aiplane->heal_damage(this->expectedDamage());

			if (child_value <= alpha) {
				delete[] possible_moves;
				return child_value;
			}

			beta = std::min(beta, child_value);
		}
	}

	delete possible_moves;
	return (maximizing ? alpha : beta);
}

std::vector<Card *> WoWBrain::returnBestCards_neogen(int howmany) {
	Sequence alpha;
	Sequence beta;
	alpha.heuristic_value = -MAX_HEURISTIC;
	beta.heuristic_value = MAX_HEURISTIC;

	std::vector<Card *> actual_sequence;

	std::cout << "launching the alpha-beta pruning algorithm" << std::endl;
	Sequence * best_choice = alphaBetaPruningStep_neogen(0, true, &alpha, &beta, &actual_sequence);

	std::cout << "computed heuristic: " << best_choice->heuristic_value << std::endl;

	std::vector<Card *> ret;
	for(unsigned int i = 0; i<howmany; i++){
		ret.push_back((best_choice->cards)[i]);
	}

	delete best_choice;

	return ret;
}

Sequence * WoWBrain::alphaBetaPruningStep_neogen(int depth, bool maximizing, Sequence * alpha, Sequence * beta, std::vector<Card *> * actual_sequence) {
	Sequence * ret;	// this will be the returned sequence

	if(depth == Game::conf.search_depth) { // leaf node
		ret = new Sequence();
		for(unsigned int i=0; i<actual_sequence->size(); i++){
			ret->cards.push_back((*actual_sequence)[i]);
		}
		ret->heuristic_value = this->computeHeuristic();

		return ret;
	}

	Card ** possible_moves;
	int possible_moves_number = 0;

	Sequence * local_alpha = new Sequence(alpha);
	Sequence * local_beta = new Sequence(beta);

	Sequence * child_sequence;

	if (maximizing) { // AI PLAYER
		possible_moves = new Card*[_aiplane->getCardSet()->cards_number];
		possible_moves_number = this->nextValidMoves(this->_aiplane, possible_moves);

		if (possible_moves_number == 0) {	// From here, there are no moves (the plane is going out)
			delete[] possible_moves;
			ret = new Sequence();
			ret->heuristic_value = -MAX_HEURISTIC;
			return ret;
		}

		for (int i = 0; i < possible_moves_number; i++) {

			// modify the status
			float restore_pos[3];
			this->_aiplane->getPosition(restore_pos);
			this->_aiplane->move(possible_moves[i]); // applies a move card
			actual_sequence->push_back(possible_moves[i]); // adds this manoeuvre to the actual sequence

			// recursive call
			child_sequence = alphaBetaPruningStep_neogen(depth + 1, !maximizing, local_alpha, local_beta, actual_sequence);

			// restore the status
			actual_sequence->pop_back();
			this->_aiplane->setX(restore_pos[0]);
			this->_aiplane->setY(restore_pos[1]);
			this->_aiplane->setT(restore_pos[2]);

			// analyze this child
			if(local_alpha->heuristic_value < child_sequence->heuristic_value){
				delete local_alpha;
				local_alpha = child_sequence;
			}
			else{	// it's just a fluffy son, let's get rid of it (alpha is greater, hence MAX player has a better chance)
				delete child_sequence;
			}

			if (local_beta->heuristic_value <= local_alpha->heuristic_value) {	// beta cut-off (MIN player can do better with different choices, so we can avoid further searching)
				delete[] possible_moves;
				ret = local_alpha;
				break;
			}
		}
		ret = local_alpha;
	}
	else{	// OPPONENT PLAYER
		possible_moves = new Card*[_opponent->getCardSet()->cards_number];
		possible_moves_number = this->nextValidMoves(this->_opponent, possible_moves);

		if (possible_moves_number == 0) {	// From here, there are no moves (the plane is going out)
			delete[] possible_moves;
			ret = new Sequence();
			ret->heuristic_value = MAX_HEURISTIC;
			return ret;
		}

		bool opponent_damaged = false, ai_damaged = false;

		for (int i = 0; i < possible_moves_number; i++) {
			opponent_damaged = false;
			ai_damaged = false;

			// modify the status
			float restore_pos[3];
			this->_opponent->getPosition(restore_pos);
			this->_opponent->move(possible_moves[i]); // applies a move card
			if (this->_aiplane->canShootTo(_opponent)) { // if there are damages to be inflicted, inflict them
				opponent_damaged = true;
				_opponent->inflictDamage(this->expectedDamage());
			}
			if (this->_opponent->canShootTo(_aiplane)) {
				ai_damaged = true;
				_aiplane->inflictDamage(this->expectedDamage());
			}

			// recursive call
			child_sequence = alphaBetaPruningStep_neogen(depth + 1, !maximizing, alpha, beta, actual_sequence);

			// restore the status
			this->_opponent->setX(restore_pos[0]);
			this->_opponent->setY(restore_pos[1]);
			this->_opponent->setT(restore_pos[2]);
			if (opponent_damaged) _opponent->heal_damage(this->expectedDamage()); // restores the damages
			if (ai_damaged) _aiplane->heal_damage(this->expectedDamage());

			// analyze this child
			if(local_beta->heuristic_value > child_sequence->heuristic_value){
				delete local_beta;
				local_beta = child_sequence;

			}
			else{	// it's just a fluffy son, let's get rid of it (beta is lower, hence MIN player has a better chance)
				delete child_sequence;
			}

			if (local_beta->heuristic_value <= local_alpha->heuristic_value) {	// alpha cut-off (MAX player can do better with different choices, so we can avoid further searching)
				delete[] possible_moves;
				ret = local_beta;
				break;
			}
		}

		ret = local_beta;
	}

	return ret;
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
	if (this->_aiplane->remainingHealth() <= 0 || !this->_current_world->isInside(this->_aiplane)) {
		return -MAX_HEURISTIC+1;
	}

	if (this->_opponent->remainingHealth() <= 0 || !this->_current_world->isInside(this->_opponent)) {
		return MAX_HEURISTIC-1;
	}

	float aipos[3];
	float opponentpos[3];
	this->_aiplane->getPosition(aipos);
	this->_opponent->getPosition(opponentpos);

	// Compute Manhattan Distance
	// I don't use this for now. It's a tricky part...
	//int manhattan = (int) abs(aipos[0] - opponentpos[0]);
	//manhattan += (int) abs(aipos[1] - opponentpos[1]);

	// Compute ShotValue
	int aivalue = _aiplane->evalueatePlanePosition(_opponent);
	int opponentvalue = _opponent->evalueatePlanePosition(_aiplane);

	//    if (_aiplane->canSee(_opponent)) {
	//        aivalue++;
	//    }
	//    if (_opponent->canSee(_aiplane)) {
	//        opponentvalue++;
	//    }
	//    if (_aiplane->canShootTo(_opponent)) {
	//        aivalue++;
	//    }
	//    if (_opponent->canShootTo(_aiplane)) {
	//        opponentvalue++;
	//    }

	int aiscore = _weights[1] * aivalue + _weights[2]*(_aiplane->remainingHealth());
	int opponentscore = _weights[1] * opponentvalue + _weights[2]*(_opponent->remainingHealth());

	return aiscore - opponentscore;
}

int WoWBrain::expectedDamage() {
	return 1;
}

Sequence::Sequence(){
}

Sequence::Sequence(Sequence * to_be_copied){
	this->heuristic_value = to_be_copied->heuristic_value;
	for(unsigned int i=0; i<to_be_copied->cards.size(); i++){
		this->cards.push_back(to_be_copied->cards[i]);
	}
}

Sequence::~Sequence(){
}

void Sequence::copy(Sequence * to_be_copied){
	this->heuristic_value = to_be_copied->heuristic_value;
	for(unsigned int i=0; i<to_be_copied->cards.size(); i++){
		this->cards.push_back(to_be_copied->cards[i]);
	}
}
