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

//	if (plane->remainingHealth() <= 0) {
//		return 0;
//	}
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

std::vector<Card *> WoWBrain::returnBestCards() {
	int alpha = INT_MIN;
	int beta = INT_MAX;

	std::vector<Card *> actual_sequence;

	std::cout << "launching the alpha-beta pruning algorithm" << std::endl;
	Card ** best_choice;
	int choice_lenght;
	int choice_heur = alphaBetaPruningStep(0, true, alpha, beta, &actual_sequence, best_choice, choice_lenght);

	std::cout << "computed heur:\t" << choice_heur << ",\tseq_lenght:\t" << choice_lenght << std::endl;
	std::vector<Card *> ret;
	if(choice_lenght >= CHOICES_PER_TURN){
		for(int i=0; i<CHOICES_PER_TURN; i++){
			ret.push_back(best_choice[i]);
		}
	}
	else{	// the plane is doomed to die
		for(unsigned int i = 0; i<CHOICES_PER_TURN; i++){
			if(i<choice_lenght){
				ret.push_back(best_choice[i]);
			}
			else{
				ret.push_back(_aiplane->getCardSet()->cards);	// just take the first card
			}
		}
	}

	delete[] best_choice;

	return ret;
}

int WoWBrain::alphaBetaPruningStep(int depth, bool maximizing, int alpha, int beta, std::vector<Card *> * actual_sequence, Card** &choice, int &choice_lenght) {
	choice = new Card*[CHOICES_PER_TURN];	// this is the returned pointer
	choice_lenght = -1;

	if(depth == Game::conf.search_depth) { // leaf node
		for(unsigned int i=0; i<CHOICES_PER_TURN; i++){
			choice[i] = (*actual_sequence)[i];
		}
		choice_lenght = CHOICES_PER_TURN;
		return this->computeHeuristic();
	}

	Card ** possible_moves;
	int possible_moves_number = 0;

	if (maximizing) { // AI PLAYER
		if (this->_aiplane->remainingHealth() <= 0){	// AIPLANE will already be dead
			for(int i=0; i<CHOICES_PER_TURN && i<actual_sequence->size(); i++){
				choice[i] = (*actual_sequence)[i];
				choice_lenght = i+1;
			}
			return MIN_HEURISTIC + 10;
		}

		possible_moves = new Card*[_aiplane->getCardSet()->cards_number];
		possible_moves_number = this->nextValidMoves(this->_aiplane, possible_moves);

		if (possible_moves_number == 0) {	// From here, there are no moves (the plane is going out)
			delete[] possible_moves;
			for(int i=0; i<CHOICES_PER_TURN && i<actual_sequence->size(); i++){
				choice[i] = (*actual_sequence)[i];
				choice_lenght = i+1;
			}
			return MIN_HEURISTIC;
		}

		for (int i = 0; i < possible_moves_number; i++) {

			// modify the status
			float restore_pos[3];
			this->_aiplane->getPosition(restore_pos);
			this->_aiplane->move(possible_moves[i]); // applies a move card
			actual_sequence->push_back(possible_moves[i]); // adds this manoeuvre to the actual sequence

			// recursive call
			Card ** child_seq;
			int child_length;
			int child_heur = alphaBetaPruningStep((depth + 1), !maximizing, alpha, beta, actual_sequence, child_seq, child_length);
			//			std::cout << "child returned: "; child_sequence->print(); std::cout << std::endl;

			// restore the status
			actual_sequence->pop_back();
			this->_aiplane->setX(restore_pos[0]);
			this->_aiplane->setY(restore_pos[1]);
			this->_aiplane->setT(restore_pos[2]);

			// analyze this child
			if(alpha < child_heur){
				alpha = child_heur;
				delete[] choice;
				choice = child_seq;
				choice_lenght = child_length;
			}
			else{	// it's just a fluffy son, let's get rid of it (alpha is greater, hence MAX player has a better chance)
				delete[] child_seq;
			}

			if (beta <= alpha) {	// beta cut-off (MIN player can do better with different choices, so we can avoid further searching)
				break;
			}
		}
	}
	else{	// OPPONENT PLAYER
		if (this->_aiplane->remainingHealth() <= 0){	// AIPLANE will already be dead
			for(int i=0; i<CHOICES_PER_TURN && i<actual_sequence->size(); i++){
				choice[i] = (*actual_sequence)[i];
				choice_lenght = i+1;
			}
			return MIN_HEURISTIC + 10;
		}

		possible_moves = new Card*[_opponent->getCardSet()->cards_number];
		possible_moves_number = this->nextValidMoves(this->_opponent, possible_moves);

		if (possible_moves_number == 0) {	// From here, there are no moves (the plane is going out)
			delete[] possible_moves;
			for(int i=0; i<CHOICES_PER_TURN && i<actual_sequence->size(); i++){
				choice[i] = (*actual_sequence)[i];
				choice_lenght = i+1;
			}
			return (MAX_HEURISTIC);
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
			Card ** child_seq;
			int child_length;
			int child_heur = alphaBetaPruningStep((depth + 1), !maximizing, alpha, beta, actual_sequence, child_seq, child_length);

			//			std::cout << "child returned: "; child_sequence->print(); std::cout << std::endl;

			// restore the status
			this->_opponent->setX(restore_pos[0]);
			this->_opponent->setY(restore_pos[1]);
			this->_opponent->setT(restore_pos[2]);
			if (opponent_damaged) _opponent->heal_damage(this->expectedDamage()); // restores the damages
			if (ai_damaged) _aiplane->heal_damage(this->expectedDamage());

			// analyze this child

			if(beta > child_heur){
				beta = child_heur;
				delete[] choice;
				choice = child_seq;
				choice_lenght = child_length;
			}
			else{	// it's just a fluffy son, let's get rid of it (beta is lower, hence MIN player has a better chance)
				delete child_seq;
			}

			if (beta <= alpha) {	// alpha cut-off (MAX player can do better with different choices, so we can avoid further searching)
				break;
			}

		}
	}

	delete[] possible_moves;
	//	std::cout << "returning: "; ret->print(); std::cout << std::endl;
	return (maximizing? alpha : beta);
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
	// The values that ShotValue can assume are specified in the Plane::evalueatePlanePosition method
	//
	// RamainingLife, instead, is just the amount of remaining life points
	// of the Plane X.
	//

	//	float aipos[3];
	//	float opponentpos[3];
	//	this->_aiplane->getPosition(aipos);
	//	this->_opponent->getPosition(opponentpos);

	// Compute ShotValue
	int aivalue = _aiplane->evalueatePlanePosition(_opponent);
	if (this->_aiplane->remainingHealth() <= 0 || !this->_current_world->isInside(this->_aiplane)) {
		aivalue = aivalue - 10000;
	}
	int opponentvalue = _opponent->evalueatePlanePosition(_aiplane);
	if (this->_opponent->remainingHealth() <= 0 || !this->_current_world->isInside(this->_opponent)) {
		opponentvalue = opponentvalue - 10000;
	}

	int aiscore = _weights[1] * aivalue + _weights[2]*(_aiplane->remainingHealth());
	int opponentscore = _weights[1] * opponentvalue + _weights[2]*(_opponent->remainingHealth());

	return aiscore - opponentscore;
}

int WoWBrain::expectedDamage() {
	return 1;
}

Sequence::Sequence(){
	this->cards_initialized = false;
}

Sequence::Sequence(Sequence * to_be_copied){
	this->cards = new std::vector<Card*>();
	this->cards_initialized = true;
	this->heuristic_value = to_be_copied->heuristic_value;
	for(unsigned int i=0; i<to_be_copied->cards->size(); i++){
		this->cards->push_back((*to_be_copied->cards)[i]);
	}
}

Sequence::~Sequence(){
	if(this->cards_initialized){
		delete this->cards;
	}
}

void Sequence::initCards(){
	this->cards = new std::vector<Card*>();
	this->cards_initialized = true;
}

bool Sequence::cardsExist(){
	return this->cards_initialized;
}

void Sequence::copy(Sequence * to_be_copied){
	if(this->cards_initialized){
		delete this->cards;
	}
	this->heuristic_value = to_be_copied->heuristic_value;
	if(to_be_copied->cardsExist()){
		this->cards_initialized = true;
		this->cards = to_be_copied->cards;
	}
	else{
		this->cards_initialized = false;
	}
}

void Sequence::print(){
	if(cards_initialized){
		std::cout << "seq_length = " << this->cards->size();
	}
	else{
		std::cout << "no_cards";
	}
	std::cout << ", heurValue = " << this->heuristic_value;
}
