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
    
    Game* gioco = new Game(600,800,32);
    gioco->init();
    /*
    Plane p1(1,15,0,0,0);
    
    float position[3];
 
    CardSet cset;
    cset.cards_number = 3;
    
//    cset.cards = new Card*[3];
//    
//    cset.cards[0] = new Card[3];
//    cset.cards[1] = cset.cards[0];
//    cset.cards[2] = cset.cards[1];
//    
//    Card::CType * typebuffer = (Card::CType *)malloc(sizeof(Card::CType));
//    
//    cset.cards[0]->setMovement(10,2,M_PI/6);
//    cset.cards[0]->setType(Card::L_STEER);
//    cset.cards[1]->setMovement(6,-2,-M_PI/4);
//    cset.cards[1]->setType(Card::R_STEER);
//    cset.cards[2]->setMovement(12,0,0);
//    cset.cards[2]->setType(Card::STRAIGHT);
//    
//    for(int i=0; i<cset.cards_number; i++){
//        (*cset.cards)[i].getMovement(position);
//        *typebuffer = (*cset.cards)[i].getCardType();
//        cout << "\nmanoeouvre n." << i+1 << ":\n";
//        cout << "card type: " << (*typebuffer==Card::L_STEER?"left steer":(*typebuffer==Card::R_STEER?"right steer":"straight")) << '\n';
//        cout << "dx: " << position[0] << "; dy: " << position[1] << "; dtheta: " << position[2] << '\n';
//    }
//    
//    cout << '\n';
//    
//    free(typebuffer);
//    
//    delete  [] *cset.cards;
//    
//    delete cset.cards;
    
    return 0;
     * 
     */
}