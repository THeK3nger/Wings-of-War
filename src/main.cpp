#include "Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Game* gioco = new Game(600, 800, 32);
    gioco->mainGameLoop();
    delete gioco;

    return 0;
}
