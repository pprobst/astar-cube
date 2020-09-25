#include "cube.hpp"
#include "search.hpp"

int main(int argc, char **argv) {
    // Random seed.
    srand(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

    // Default config.
    int cube_dim = 100;
    float blocker_percent = 40;
    Location start = Location(-1, -1, -1);
    Location goal = Location(-1, -1, -1);
    bool record = false;

    if (argc == 1) {
        cout << "No arguments inserted (see README). Default settings used." << endl;
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i],"-r")==0) {
                record = true;
            } else if (strcmp(argv[i],"-d")==0) {
                cube_dim = atoi(argv[i+1]);
            } else if (strcmp(argv[i],"-b")==0) {
                blocker_percent = atoi(argv[i + 1]);
            } else if (strcmp(argv[i],"-s")==0) {
                int x1 = atoi(argv[i + 1]);
                int y1 = atoi(argv[i + 2]);
                int z1 = atoi(argv[i + 3]);
                start = Location(x1, y1, z1);
            } else if (strcmp(argv[i],"-g")==0) {
                int x2 = atoi(argv[i + 1]);
                int y2 = atoi(argv[i + 2]);
                int z2 = atoi(argv[i + 3]);
                goal = Location(x2, y2, z2);
            }
        }
    }

    Cube* cube = new Cube(cube_dim);

    if (start.getX() == -1 || goal.getX() == -1) {
        cube->setStart(cube->getRandomLoc());
        cube->setGoal(cube->getRandomLoc());
    } else {
        cube->setStart(start);
        cube->setGoal(goal);
    }

    cube->makeObstacles(blocker_percent);

    int size = cube->getSize();
    cout << "> Cube dimensions: " << size << "x" << size << "x" << size << endl;
    cout << "> Blockers: " <<  blocker_percent << "%" << endl;
    cout << "> Start: " << cube->getStart() << endl;
    cout << "> Goal: " << cube->getGoal() << endl;

    unordered_map<Location, Location> origin;
    double dist = 0;

    auto t0 = std::chrono::high_resolution_clock::now();
    if (Search::astar(*cube, cube->getStart(), cube->getGoal(), origin, dist)) {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> fp_ms = t1 - t0;
        cout << ">> Goal found!" << endl;
        cout << "> Path:" << endl;
        for (Location loc : Search::path(cube->getStart(), cube->getGoal(), origin)) {
            cout << "  -> " << loc.getPoint() << endl;
        }
        cout << "Distance from " << cube->getStart() << " to " << cube->getGoal() << ": " << dist << endl;
        cout << "Time: " << fp_ms.count()  << " ms" << endl;
        if (record) {
            ofstream outfile;
            outfile.open("times.csv", ios_base::app); // append instead of overwrite
            outfile << dist << "," << fp_ms.count()  << endl;
        }
    } else {
        // Unreachable results are not recorded in times.csv
        cout << "Goal is unreachable (obstructed path; maybe lower the \% of obstructions?)." << endl;
    }

    return 0;
}
