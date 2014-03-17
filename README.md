Maze
====
Solving a maze with A* algorithm using C++.

The type priority_queue in the STL library is employed as it allows to customize element’s order within the set.


###Execute Example
*Here is a program that solves a maze using A * algorithm*  
*The program firstly allows you to input the maze detail, then calculates the solution*  
*Input: length & width. Example: 5 5*  
8 8  
*input the maze*  
**0** 0 1 1 1 1 1 1  
1 0 0 0 0 1 0 **0**  
1 1 0 1 0 1 0 1  
0 0 0 1 0 1 0 1  
0 1 1 1 0 1 0 1  
0 1 0 0 0 1 0 1  
0 1 1 1 1 1 0 1  
0 0 0 0 0 0 0 1  
*Input the coordinate of initial node & destination node. Example: 1 1 5 5*  
1 1 2 8  
*Calculating solution with A star algorithm:*  
*(1,1),(1,2),(2,2),(2,3),(3,3),(4,3),(4,2),(4,1),(5,1),(6,1),(7,1),(8,1),(8,2),(8,3),(8,4),(8,5),(8,6),(8,7),(7,7),(6,7),(5,7),(4,7),(3,7),(2,7),(2,8)*  
*Steps count: 24*  
