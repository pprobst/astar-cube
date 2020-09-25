#include "search.hpp"
#include "pqueue.hpp"

bool Search::astar(Cube cube, Location start, Location goal,
        unordered_map<Location, Location> &origin, double &dist) {

    // Costs map: <location> and <cost>.
    unordered_map<Location, double> cost; // A C++ map is like a Python dict and utilizes hash functions for fast lookup.
    // Priority Queue: <location> and <cost+heuristic> (modified to get the lowest value instead of the highest).
    // The elements in the fringe are the OPEN set.
    PQueue<Location, double> fringe;

    int size = cube.getSize();
    vector<bool> closed(size*size*size, false); // Initialize this as a filled array of falses so the search in it is not costly.

    fringe.add(start, 0);

    // 'origin' keys are the REACHED set. In mathematical terms, we can infer that REACHED = OPEN U CLOSED.
    origin[start] = start;
    cost[start] = 0;

    while (!fringe.empty()) {
        Location curr = fringe.get(); // curr is the element with lowest cost.
        closed[curr.toIndex(size, size)] = true; // toIndex to get the index location for location curr (saves a ton of processing time!).

        if (curr == goal) {
            dist = cost[curr];
            return true;
        }

        // Neighbors are valid (always inside the cube) and passable (not blockers).
        for (Location neighbor : cube.getNeighbors(curr)) {
            double new_cost = cost[curr] + 1; // + 1 because the movement cost is fixed.

            // Using a separate 'closed' set in this case actually uneeded, as origin is actually the UNION between
            // the CLOSED and OPEN (fringe) sets. But it speeds up the algorithm in ~500 ms when using 100x100x10 (long distances).
            if (closed[neighbor.toIndex(size, size)]) {
                // Because Euclidean distance is a consistent and admissible heuristic, we don't need to take anything out of
                // the closed set.
                continue;
            }
            // In C++, unlike Java we can't take an specific element from the priority queue. So we'll just update it.
            // This is because if it was manually implemented, the cost would be O(n) and O(n^2) worst case.
            if (cost.find(neighbor) == cost.end() || new_cost < cost[neighbor]) {
                cost[neighbor] = new_cost;
                double total_cost = new_cost + heuristic(neighbor, goal); // f = g + h
                fringe.add(neighbor, total_cost);
                origin[neighbor] = curr; // Attributes the current node as the parent of neighbor.
            }
        }
    }

    return false;
}

vector<Location> Search::path(Location start, Location goal,
        unordered_map<Location, Location> origin) {

    vector<Location> path;
    Location curr = goal;

    while (curr != start) {
        path.push_back(curr);
        curr = origin[curr];
    }

    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}
