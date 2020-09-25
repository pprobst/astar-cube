#include "location.hpp"

Location::Location(int x, int y, int z) {
    this->point = Point{x, y, z};
    this->blocker = false;
}

Location::Location() {
    this->point = Point{0, 0, 0};
    this->blocker = false;
}


void Location::setBlocker() { this->blocker = true; }

void Location::setPoint(int x, int y, int z) {
    this->point.x = x;
    this->point.y = y;
    this->point.z = z;
}

int Location::toIndex(int height, int width) {
    return this->getX() + height * (this->getY() + width * this->getZ());
}

Point Location::getPoint() const { return this->point; }

int Location::getX() const { return this->point.x; }

int Location::getY() const { return this->point.y; }

int Location::getZ() const { return this->point.z; }

bool Location::isBlocker() const { return this->blocker; }
