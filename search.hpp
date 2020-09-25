#ifndef _SEARCHH_
#define _SEARCHH_

#include "cube.hpp"

class Search {
    public:
        /**
         * Runs the A* algorithm.
         * Return True if goal found.
         */
        static bool astar(Cube cube, Location start, Location goal,
                unordered_map<Location, Location> &origin,
                double &dist);

        /**
         * Retraces the path from the Start to the Goal.
         */
        static vector<Location> path(Location start, Location goal,
                unordered_map<Location, Location> origin);

};

/**
 * The heuristic used (Euclidean distance between two points).
 */
inline double heuristic(Location a, Location b) {
    return sqrt((pow(b.getX()-a.getY(), 2) +
                pow(b.getY()-a.getY(), 2) +
                pow(b.getZ()-a.getZ(), 2)));
}

#endif
