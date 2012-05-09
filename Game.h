#ifndef GAME_H
#define	GAME_H

#include "Plane.h"
#include "World.h"
#include "WoWBrain.h"

/*!
 * \brief This class is the core class of the Game.
 * 
 * It contains various stuff to execute the game.
 */
class Game {
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
private:
    World* world;
    WoWBrain* ai;
};

#endif	/* GAME_H */

