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
 
    Card *n1 = new Card(Card::R_STEER,10,-2,-M_PI/4);
    
    p1.move(n1);
    p1.getPosition(position);
    cout << "plane position after applying n1: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p1.move(n1);
    p1.getPosition(position);
    cout << "plane position after applying n1 again: " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    p1.revertMove(n1);
    p1.revertMove(n1);
    p1.getPosition(position);
    cout << "plane position after reverting n1 (2 times): " << position[0] << ' ' << position[1] << ' ' << position[2] << '\n';
    cout.flush();
    
    Plane *p2 = new Plane(2, 15, 1, 0, 0);
    
    cout << "plane 1 " << (p1.canShootTo(p2)?"CAN":"CANNOT") << " shoot to plane 2\n";
    cout.flush();
    
    delete n1;
    delete p2;
    
    return 0;
}

