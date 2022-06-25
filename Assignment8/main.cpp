#include <iostream>
#include <vector>
#include "Maze.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    
    Maze m(6);
    m.createDefaultMaze();

    m.createPath(0, 1); 
    m.createPath(0, 2);
    m.createPath(0, 3);
    m.createPath(0, 4);
    m.createPath(0, 5); 
    m.createPath(1, 5);
    m.createPath(2, 5);
    m.createPath(3, 5);
    m.createPath(4, 5);

/*
    m.createPath(0, 6); 
    m.createPath(6, 7); 
    m.createPath(6, 11);
    m.createPath(7, 3);
    m.createPath(7, 8);
    m.createPath(7, 13); 
    m.createPath(3, 8);
    m.createPath(8, 13);
    m.createPath(11, 15);
    m.createPath(11, 17);
    m.createPath(13, 17); 
    m.createPath(15, 21); 
    m.createPath(17, 21); 
    m.createPath(17, 23); 
    m.createPath(23, 24);
    */

    // m.createPath(0, 3); 
    // m.createPath(1, 1); 
    // m.createPath(1, 2);
    // m.createPath(1, 3);
    // m.createPath(2, 1);
    // m.createPath(2, 3); 
    // m.createPath(2, 4);
    // m.createPath(3, 0);
    // m.createPath(3, 2);
    // m.createPath(4, 1);
    // m.createPath(4, 3);   
         
    m.printMaze();
    
    m.convertMazeToAdjacencyListGraph();
    m.displayEdges();

    cout << "\n" << endl;
    m.findPathThroughMaze();
    cout << "\nIs valid path?" << endl;
    cout << m.checkIfValidPath() << endl;
    

    return 0;
}
