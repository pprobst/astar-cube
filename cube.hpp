#ifndef _CUBEH_
#define _CUBEH_

#include "location.hpp"

typedef vector<vector<vector<Location>>> grid3d;

class Cube {
    private:
        int size; // e.g. 10 -> 10x10x10
        Location start; // Start location.
        Location goal; // Goal location.
        grid3d grid; // Cubic grid.

    public:
        /**
         * Possible movements inside the cube.
         */
        static array<Location, 6> DIRS;

        Cube(size_t size);

        /**
         * Initializes a constructed Cube with data.
         */
        void setData(Location start, Location goal, float percent_blockers);

        /**
         * Make random obstacles (blocker tiles) in the cube.
         */
        void makeObstacles(float percent);

        void setStart(Location loc);

        void setGoal(Location loc);

        bool isStart(Location loc) const;

        bool isGoal(Location loc) const;

        /**
         * Checks if the location is inside the cube.
         */
        bool isValid(Location loc) const;

        /**
         * Checks if the location is not a blocker.
         */
        bool isPassable(Location loc) const;

        /**
         * Gets cube size.
         */
        int getSize() const;

        /**
         * Gets a random valid location from the cube.
         *
         * @return Location.
         */
        Location getRandomLoc();

        /**
         * Gets actual location from the cube from the coords given.
         */
        Location getLoc(int x, int y, int z) const;

        /**
         * Gets actual location from the cube from the loc given.
         */
        Location getLoc(Location loc) const;

        Location getStart();

        Location getGoal();

        /**
         * Gets neighbors of the location given.
         */
        vector<Location> getNeighbors(Location loc) const;
};

#endif
