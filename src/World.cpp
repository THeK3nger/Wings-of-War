#include "World.h"

World::World(float w, float h) :
    width(w), height(h)
{}

World::~World() {
}

void World::draw() {

}

Plane* World::GetPlaneById(int id) {
    for (int i = 0; i<this->planes.size(); i++) {
        if (this->planes[i]->getId() == id)
            return this->planes[i];
    }
    return 0;
}

void World::addPlane(Plane* plane) {
    this->planes.push_back(plane);
}

float World::getHeight() const {
    return height;
}

float World::getWidth() const {
    return width;
}

std::vector<Plane*> * World::getPlanes() {
    return &this->planes;
}
