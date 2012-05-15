/* 
 * File:   main.cpp
 * Author: Iron Man, Thor, Hulk
 *
 * Created on May 7, 2012, 6:26 PM
 */

#include <cstdlib>
#include <iostream>
#include "Plane.h"
#include "Card.h"
#include "Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Plane * p1 = new Plane(1,20,10,10,0);
    Plane * p2 = new Plane(2,20,15,10,M_PI);
    
    World * world = new World(100, 100);
    
    world->addPlane(p1);
    world->addPlane(p2);
    
    Card cards[3];
    cards[0].setType(Card::R_STEER);
    cards[0].setMovement(5,-5,-M_PI/4);
    
    cards[1].setType(Card::L_STEER);
    cards[1].setMovement(5,5,M_PI/4);
    
    cards[2].setType(Card::STRAIGHT);
    cards[2].setMovement(10,0,0);
    
    
    CardSet cset;
    cset.cards = cards;
    cset.cards_number = 3;
    
    p1->setCardSet(&cset);
    p2->setCardSet(&cset);
    
    WoWBrain * ai = new WoWBrain(p1,world);
    
    std::vector<Card*> moves = ai->returnBestCards(20);
    
    std::cout << "sequence size: " << moves.size() << '\n';
    std::cout << "sequence: ";
    for (int i=0; i<moves.size(); i++){
        std::cout << (moves[i]->getCardType() == Card::R_STEER? "RIGHT ":(moves[i]->getCardType() == Card::L_STEER? "LEFT ": "STRAIGHT"));
    }
    std::cout << '\n';
}