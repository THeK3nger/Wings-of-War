#include "World.h"

World::World(float w, float h) {
    this->width = w;
    this->height = h;
    this->planes = std::vector<Plane*>();
}

World::~World() {
}

void World::draw(){
    
}

Plane* World::GetPlaneById(int id){
    for (int i=0; i<this->planes.size(); i++){
        if(this->planes[i]->getId() == id)
            return this->planes[i];
    }
    return 0;
}

void World::addPlane(Plane* plane){
    this->planes.push_back(plane);
}

float World::getHeight() const {
    return height;
}

float World::getWidth() const {
    return width;
}

std::vector<Plane*> * World::getPlanes(){
    return &this->planes;
}

bool World::isInside(Plane* plane){
    float pos[3];
    plane->getPosition(pos);
    if(pos[0] < 0) return false;
    if(pos[1] < 0) return false;
    if(pos[0] > this->width) return false;
    if(pos[1] > this->height) return false;
    return true;
}