#ifndef PLANE_H
#define	PLANE_H

#include "Card.h"
#include <math.h>
#include <vector>

#define SHOOTING_RADIUS 10
#define SHOOTING_ANGLE  M_PI/6 // this expresses the randiants in ONE direction, so the actual shooting angle is twice this number

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
    
    /*!
     * Apply the reverted movement of the given Card.
     * \param card The card representing the movement to revert
     */
    void revertMove(Card card);
    
    /*!
     *  Returns the difference between the maximum health value of this Plane and the damage it has received
     */
    int remainingHealth();
    
    /*!
     * Returns the Maximum Health Value for this Plane (I.E. the initial value)
     */
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
     * Sets the type of the last used move.
     */
    void setLastMove(Card::CType last_move_type);
    
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
    // TODO: Card List must be a reference. I remove this for now.
    //std::vector<Card> cards;    // Manoeuvre cards for this plane
                                // TODO -- I think it is a good idea to put the cards list
                                //         in the plane itself, because (in the extended game) every
                                //         plane has a set of manoeuvres, that contribute to its
                                //         characterization. The alternative is to put it in the
                                //         "WoWBrain" Class
    
};

#endif	/* PLANE_H */

