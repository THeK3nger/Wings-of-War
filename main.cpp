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