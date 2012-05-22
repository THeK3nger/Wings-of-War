/* 
 * File:   Animation.h
 * Author: fabrizio
 *
 * Created on May 22, 2012, 1:39 PM
 */

#ifndef ANIMATION_H
#define	ANIMATION_H

/*!
 * \brief Animation Class. This manages the interpolation of the movements in the game
 * 
 * It takes into account the initial and final values of the movement,
 * and allows an easy access to intermediate points coordinates.
 */
class Animation{
        private:
            float init_x;           // initial value of x
            float init_y;           // initial value of y
            float init_theta;       // initial value of theta
            float final_x;          // final value of x
            float final_y;          // final value of y
            float final_theta;      // final value of theta
            float cx1, cx2, cx3;    // coefficients for the x component
            float cy1, cy2, cy3;    // coefficients for the y component
            float k;          // "gain" coefficient TODO: adapt it to the movement
            float s;                // will keep track of the amount of animation elapsed
            float step;      // this affects the number of iterations needed for completing the animation
            float prev_pos[2];      // this the previous position, used for computing the angle
            
        public:
            /*!
             * Constructor. Initializes the initial values and computes the relative coefficients
             * 
             * \param xi value of the x coordinate in the initial position
             * \param yi value of the y coordinate in the initial position
             * \param thetai value of the theta coordinate in the initial position
             * \param xf value of the x coordinate in the final position
             * \param yf value of the y coordinate in the final position
             * \param thetaf value of the theta coordinate in the final position
             */
            Animation(float xi, float yi, float thetai, float xf, float yf, float thetaf);
            
//            /*!
//             * Another constructor, allows the creation of an Animation using
//             * different inputs.
//             * 
//             * \param pos A 3 floats array containing the initial position of the plane
//             * \param the Card that represents the desired movement
//             */
//            Animation(float * init_pos, Card * card);
            
            /*!
             * retrieves the next position.
             * \param pos A 3 floats array where the method will store the next position
             * 
             * \return False if there are no more steps to do (s==1), True otherwise
             */
            bool nextStep(float *pos);
            
};


#endif	/* ANIMATION_H */

