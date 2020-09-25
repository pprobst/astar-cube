# astar-cube
The A* algorithm running on a cube (3D space). Wirrten for learning purposes.

### Running
```
$ make
```

For default config: (100x100x100, 40% blockers, random start, random goal)
```
$ ./astar
```

For custom config: 
```
$ ./astar -d CUBE_DIMENSION -b BLOCKER_PERCENT -s START_X START_Y START_Z -g GOAL_X GOAL_Y GOAL_Z
```

E.g. 50x50x50, 10% blockers, start at (12, 12, 12), goal at (30, 30, 30):
```
$ ./astar -d 50 -b 10 -s 12 12 12 -g 30 30 30
```

If you'd like to record the results in ```times.csv```, insert the ```-r```
argument.

The ```stats.py``` script makes a distance x time plot like ```graph.png```
based on the data recorded.

### References
https://www.redblobgames.com/pathfinding/a-star/introduction.html
