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
class World {
private:
    float width;
    float height;
    std::vector<Plane*> planes;

public:
    World(float w, float h);
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

    /*!
     * Add a single Plane to the World
     * 
     * \param plane A reference to the new Plane.
     */
    void addPlane(Plane* plane);

    /*!
     * Tells whether the given plane is inside the boundaries or not
     * 
     * \return True if the plane is inside, False otherwise
     */
    inline bool isInside(Plane* plane) {
        float pos[3];
        plane->getPosition(pos);
        if (pos[0] < 0 || pos[1] < 0) return false;
        if (pos[0] > this->width || pos[1] > this->height) return false;
        return true;
    }

    /*! GETTER */
    float getHeight() const;
    float getWidth() const;
    std::vector<Plane*> * getPlanes();

};

#endif	/* WORLD_H */