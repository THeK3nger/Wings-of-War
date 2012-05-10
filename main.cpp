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
    
    Plane p(1,15,0,0,0);
    Card c1(Card::STRAIGHT, 10, 0, 0);
    Card c2(Card::L_STEER, 2, 2, M_PI/4);
    Card c3(Card::L_STEER, 2, 2, M_PI/4);
    
    float position[3];
    
    p.getPosition(position);
    cout << "plane initial position: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p.move(c1);
    p.getPosition(position);
    cout << "plane position after applying c1: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p.move(c2);
    p.getPosition(position);
    cout << "plane position after applying c2: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p.move(c3);
    p.getPosition(position);
    cout << "plane position after applying c3: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p.revertMove(c3);
    p.getPosition(position);
    cout << "plane position after reverting c3: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p.revertMove(c2);
    p.getPosition(position);
    cout << "plane position after reverting c2: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p.revertMove(c1);
    p.getPosition(position);
    cout << "plane position after reverting c1: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    return 0;
}

