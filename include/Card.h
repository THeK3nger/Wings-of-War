#ifndef CARD_H
#define	CARD_H

/*!
 * \brief Card Class. It represents a movement card of the game.
 * 
 * It is described by the variation of an airplane position assuming that its
 * "theta" is equal to zero. In general case, delta-vector must be rotated.
 * 
 * For example, if `Plane` A has position (x,y) and rotation theta, a `Card` 
 * moves it to 
 * 
 *     x = x + dx * cos(theta) - dy * sin(theta)
 *     y = y + dx * sin(theta) + dy * cos(theta)
 *     theta = theta + dtheta
 * 
 * Where dx, dy and dtheta are the attributes of this class.
 */
class Card {
public:

    /*!
     * Describe the card type. (for now only 3)
     */
    // LATER THEY WILL BE "dangerous", "normal", "straight", "himmelmann"
    // The curves will be specified via the x, y and theta in the card

    enum CType {
        STRAIGHT,
        R_STEER,
        L_STEER,
    };

    Card();

    Card(CType type, float mov_x, float mov_y, float mov_theta);
    virtual ~Card();

    /*!
     * Returns Card movement.
     * 
     * \param outMove Output array. Should be size 3 at least.   
     */
    void getMovement(float* outMove);

    /*!
     * Returns Card type
     * 
     * \return The Card type     
     */
    CType getCardType();

    void setMovement(float x, float y, float theta);

    void setType(CType type);

private:
    float dx; // Variation along x axis.
    float dy; // Variation along y axis.
    float dtheta; // Variation of theta value.
    CType type; // Card type.
};

#endif	/* CARD_H */

