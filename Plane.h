#ifndef PLANE_H
#define	PLANE_H

#include "Card.h"
#include <math.h>

#define SHOOTING_RADIUS 10
#define SHOOTING_ANGLE  60

/*!
 * \brief This class represents an airplane of the game "Wings-of-War".
 * 
 * A `Plane` is described by its position and its health-points.
 */
class Plane {
public:
    
    Plane(int id, int health, float x, float y, float theta);
    virtual ~Plane();
    
    /*!
     * Apply a movement Card `card` to this Plane.
     * 
     * \param card The desired movement card.
     */
    void move(Card card);
    
    int remainingHealth();
    int getMaxHealth();
    
    /*!
     * Return Plane ID.
     * 
     * It's useful to distinguish between AI and Humane Planes.
     * 
     * \return The Plane ID
     */
    int getId();
    
    /*!
     * Inflict damage to Plane.
     * 
     * \param amount Amount of damage sustained by the Plane.
     */
    void inflictDamage(int amount);
    
    /*!
     * Return the current Plane position and orientation.
     * 
     * \param outPosition Output array. Should be size 3 at least.
     */
    void getPosition(float* outPosition);
    
    /*!
     * Return type of the last used move.
     * 
     * \return The type of the last move.
     */
    int getLastMove();
    
    /*!
     * Check if a move Card `card` is valid or not.
     * 
     * \param card Move Card to be checked.
     * \return True if the Card is valid, False otherwise.
     */
    bool moveIsValid(Card card);
    
    /*!
     * Checks whether this plane can shoot to the target plane
     * 
     * \param target Target plane
     * \return True if the target Plane is shootable, False otherwise
     */
    bool canShootTo(Plane target);      // TODO - WATCH OUT! If we want to use more than one plane per team, we should add a vector of planes as input, to check whether there are other planes in the line (planes in the line prevent shooting) [H]
    
private:
       
    float posx;         // Current Position on the X axis.
    float posy;         // Current Position on the Y axis.
    float theta;        // Current Orientation
    
    int id;             // Plane ID
    
    int damage;                 // Accumulated Damage
    int health;                 // Max Health
    Card::CType lastmove;       // Type of the last move.
    
};

#endif	/* PLANE_H */

