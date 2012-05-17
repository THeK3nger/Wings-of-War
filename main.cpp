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

    Game* gioco = new Game(600, 800, 32);
    gioco->init();
    
    return 0;
}