#ifndef PLANE_H
#define	PLANE_H

#include "Card.h"
#include <math.h>

#define SHOOTING_RADIUS 10;
#define SHOOTING_ANGLE  60;

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
    
    //TODO: Check this getter. I don't like it. [IM]
    int getDamage();
    int getHealth();
    
    /*!
     * Return Plane ID.
     * 
     * It's useful to distinguish between AI and Humane Planes.
     * 
     * \return The Plane ID
     */
    int getId();
    
    //TODO: Check this name. I don't like it. [IM]
    // I agree, what about "incrementDamage(int damage_to_add)"?
    void setDamage(int value);
    
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

