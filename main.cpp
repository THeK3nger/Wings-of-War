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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Plane p1(1,15,0,0,0);
    
    float position[3];
 
    CardSet cset;
    cset.cards_number = 3;
    
    cset.cards = new Card*[3];
    
    Card * cards = new Card[3];
    
    Card::CType * typebuffer = (Card::CType *)malloc(sizeof(Card::CType));
    
    cards[0].setMovement(10,2,M_PI/6);
    cards[0].setType(Card::L_STEER);
    cards[1].setMovement(6,-2,-M_PI/4);
    cards[1].setType(Card::R_STEER);
    cards[2].setMovement(12,0,0);
    cards[2].setType(Card::STRAIGHT);
    
    
//    cset.cards[0] = &(cards[0]); // it's just cards
//    cset.cards[1] = &(cards[1]); // it's cards++
//    cset.cards[2] = &(cards[2]); // it's again cards++
    
    cset.cards[0] = cards;
    cset.cards[1] = cards+1;
    cset.cards[2] = cards+2;
    
    for(int i=0; i<cset.cards_number; i++){
        (*cset.cards)[i].getMovement(position);
        *typebuffer = (*cset.cards)[i].getCardType();
        cout << "\nmanoeouvre n." << i+1 << ":\n";
        cout << "card type: " << (*typebuffer==Card::L_STEER?"left steer":(*typebuffer==Card::R_STEER?"right steer":"straight")) << '\n';
        cout << "dx: " << position[0] << "; dy: " << position[1] << "; dtheta: " << position[2] << '\n';
    }
    
    cout << '\n';
    
    free(typebuffer);
    
    // one of the following two solutions is ok
//    delete [] cards;
    delete  [] *cset.cards;
    
    delete cset.cards;
    
    return 0;
}