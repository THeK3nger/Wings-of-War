/* 
 * File:   World.h
 * Author: Iron Man, Thor, Hulk
 *
 * Created on May 7, 2012, 6:45 PM
 */

#include "Plane.h"
#include <vector>

#ifndef WORLD_H
#define	WORLD_H

class World{
    float width;
    float height;
    std::vector<Plane> planes;

        public:
        World(float w, float h, std::vector<Plane> p);
        ~World();
        void draw();
        Plane* GetAereoById(int id); // return pointer of the plane
};

#endif	/* WORLD_H */