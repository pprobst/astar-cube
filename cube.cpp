#include "cube.hpp"

Cube::Cube(size_t size) {
    this->size = size;
    this->grid = grid3d(size, vector<vector<Location>>(size, vector<Location>(size)));

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                this->grid[i][j][k].setPoint(i, j, k);
            }
        }
    }
}

void Cube::setData(Location start, Location goal, float percent_blockers) {
    this->setStart(start);
    this->setGoal(goal);
    this->makeObstacles(percent_blockers);
}

void Cube::makeObstacles(float percent) {
    int num_obstacles = ceil(pow((float)this->size, 3) * (percent / 100.0));
    int cont = 0;

    while (cont < num_obstacles) {
        Location loc = this->getRandomLoc();
        if (!this->isStart(loc) && !this->isGoal(loc) && this->isValid(loc) && this->isPassable(loc)) {
            this->grid[loc.getX()][loc.getY()][loc.getZ()].setBlocker();
            cont++;
        }
    }
}

void Cube::setStart(Location loc) { this->start = loc; }

void Cube::setGoal(Location loc) {
    while (loc == this->start)
        loc = this->getRandomLoc();
    this->goal = loc;
}

bool Cube::isStart(Location loc) const { return loc == this->start; }

bool Cube::isGoal(Location loc) const { return loc == this->goal; }

bool Cube::isValid(Location loc) const {
    return 0 <= loc.getX() && loc.getX() < size
        && 0 <= loc.getY() && loc.getY() < size
        && 0 <= loc.getZ() && loc.getZ() < size;
}

bool Cube::isPassable(Location loc) const {
    return !this->getLoc(loc).isBlocker();
}


/**
 * GETTERS
 */

int Cube::getSize() const { return this->size; }

Location Cube::getRandomLoc() {
    size_t x = rand() % this->size;
    size_t y = rand() % this->size;
    size_t z = rand() % this->size;
    return Location(x, y, z);
}

Location Cube::getLoc(int x, int y, int z) const { return this->grid[x][y][z]; }

Location Cube::getLoc(Location loc) const {
    return this->grid[loc.getX()][loc.getY()][loc.getZ()];
}

Location Cube::getStart() { return this->start; }

Location Cube::getGoal() { return this->goal; }

/**
 * Right, Left
 * Front, Back
 * Up, Down
 */
array<Location, 6> Cube::DIRS =
    { Location{1, 0, 0}, Location{-1, 0, 0},
      Location{0, 1, 0}, Location{0, -1, 0},
      Location{0, 0, 1}, Location{0, 0, -1} };

vector<Location> Cube::getNeighbors(Location loc) const {
    vector<Location> neighbors;

    for (Location dir : this->DIRS) {
        Location next = Location(loc.getX() + dir.getX(),
                                 loc.getY() + dir.getY(),
                                 loc.getZ() + dir.getZ());
        if (this->isValid(next)) {
            Location actual_loc = this->getLoc(next);
            if (this->isPassable(actual_loc)) neighbors.push_back(next);
        }
    }

    return neighbors;
}
