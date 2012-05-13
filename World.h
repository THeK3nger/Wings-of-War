#include "Plane.h"
#include <vector>

#ifndef WORLD_H
#define	WORLD_H

/*!
 * This class represents the World. The empty area in which the Planes are 
 * allowed to move.
 * 
 * This is described by width, height and the Planes in-game.
 */
class World{
    private:
        float width;
        float height;
        std::vector<Plane> planes;

    public:
        World(float w, float h, std::vector<Plane> p);
        ~World();
        
        /*!
         * Rendering Function (more info in a far future)
         */
        void draw();
        
        /*!
         * Return a Plane according to its ID.
         * 
         * TODO: It's useful? Let's see...
         * 
         * \param id Desired Plane ID.
         * \return The Plane with the desired ID.
         * 
         */
        Plane* GetPlaneById(int id);
        
        /*! GETTER */
        float getHeight() const;
        float getWidth() const; 
        std::vector<Plane> * getPlanes();
        
};

#endif	/* WORLD_H */