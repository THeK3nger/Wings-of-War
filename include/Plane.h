#ifndef PLANE_H
#define	PLANE_H

#include "Card.h"
#include <math.h>
#include <vector>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#define SHOOTING_RADIUS 250
#define SHOOTING_ANGLE  M_PI/6 // this expresses the randiants in ONE direction, so the actual shooting angle is twice this number

struct CardSet {
    Card * cards;
    int cards_number; // the cards number will become a macro if all the planes have the same cards number
};

/*!
 * \brief This class represents an airplane of the game "Wings-of-War".
 * 
 * A `Plane` is described by its position and its health-points.
 */
class Plane {
public:

    Plane(int id, int health, float x, float y, float theta);
    virtual ~Plane();

    sf::Image plane_image;
    sf::Sprite plane_sprite;

    // I added the following method to avoid having a huge Plane constructor
    /*!
     * Assigns the given cards set to this Plane
     * 
     * \param cset the CardSet struct to assign to this plane
     */
    void setCardSet(CardSet *cset);

    /*!
     * Returns a pointer to the cardSet associated to this Plane
     */
    CardSet* getCardSet();

    /*!
     * Apply a movement Card `card` to this Plane.
     * 
     * \param card Pointer to the desired movement card.
     * \return True if the move has been applied, False otherwise
     */
    bool move(Card *card);

    /*!
     * Apply the reverted movement of the given Card.
     * \param card Pointer to the card representing the movement to revert
     */
    void revertMove(Card *card, Card::CType prev_lastmove);

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
     * Restores plane health
     * 
     * \param amount Amount of damage to heal
     */
    void heal_damage(int amount);

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
    Card::CType getLastMove();

    /*!
     * Check if a move Card `card` is valid or not.
     * 
     * \param card Pointer to the Move Card to be checked.
     * \return True if the Card is valid, False otherwise.
     */
    bool moveIsValid(Card *card);

    /*!
     * Checks whether this plane can shoot to the target plane
     * 
     * \param target Pointer to the target plane
     * \return True if the target Plane is shootable, False otherwise
     */
    bool canShootTo(Plane *target); // TODO - WATCH OUT! If we want to use more than one plane per team, we should add a vector of planes as input, to check whether there are other planes in the line (planes in the line prevent shooting) [H]

    /*!
     * Checks whether this plane can see the target plane
     * 
     * \param target Pointer to the target plane
     * \return True if the target Plane is in the shooting angle, False otherwise
     */
    bool canSee(Plane *target); // I added this because sometimes (heuristic) we want to know something about the angle, even if it is not possible to shoot

    void setX(float x);
    void setY(float y);
    void setT(float t);
private:

    float posx; // Current Position on the X axis.
    float posy; // Current Position on the Y axis.
    float theta; // Current Orientation

    int id; // Plane ID

    int damage; // Accumulated Damage
    int health; // Max Health
    Card::CType lastmove; // Type of the last move.
    // TODO: Card List must be a reference. I remove this for now.
    //std::vector<Card> cards;    // Manoeuvre cards for this plane
    // TODO -- I think it is a good idea to put the cards list
    //         in the plane itself, because (in the extended game) every
    //         plane has a set of manoeuvres, that contribute to its
    //         characterization. The alternative is to put it in the
    //         "WoWBrain" Class
    CardSet* cardset;



};

#endif	/* PLANE_H */

