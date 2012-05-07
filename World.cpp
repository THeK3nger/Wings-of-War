/* 
 * File:   World.cpp
 * Author: Iron Man, Thor, Hulk
 * 
 * Created on May 7, 2012, 6:45 PM
 */

#include "World.h"

World::World(float w, float h, std::vector<Plane> p) {
    this->width = w;
    this->height = h;
    
    for (int i=0; i<p.size(); i++){
        this->planes.push_back(p[i]);
    }
}

World::~World() {
}

void World::draw(){
    
}

Plane* World::GetAereoById(int id){
    for (int i=0; i<this->planes.size(); i++){
        if(this->planes[i].getId() == id)
            return &(this->planes[i]);
    }
}