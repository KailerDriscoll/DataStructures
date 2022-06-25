#include "Maze.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Maze::Maze(int n){
    this->n = n; 
}

void Maze::addEdge(int v1, int v2){
    vertex* vertex1;
    vertex* vertex2;
    for (int i=0; i < vertices.size(); i++) {
        if (vertices[i]->num == v1) {
            vertex1 = vertices[i];
        } else if (vertices[i]->num == v2) {
            vertex2 = vertices[i];
        }
    }

    for (int i=0; i < vertex1->adj.size(); i++) {
        if (vertex1->adj[i].v->num == v2) {
            return;
        }
    }
    for (int i=0; i < vertex2->adj.size(); i++) {
        if (vertex2->adj[i].v->num == v1) {
            return;
        }
    }

    adjVertex av1;
    av1.v = vertex1;
    adjVertex av2;
    av2.v = vertex2;
    vertex1->adj.push_back(av2);
    vertex2->adj.push_back(av1);
}

void Maze::addVertex(int num){

    for (vector<vertex*>::iterator vi = vertices.begin(); vi != vertices.end(); ++vi) {
        if ((*vi)->num == num) {
            return;
        }
    }
    vertex* newVertex = new vertex;
    newVertex->num = num;
    vertices.push_back(newVertex);
}

void Maze::displayEdges(){
    for (int i=0; i<vertices.size(); i++) {
        cout << vertices[i]->num << " --> ";
        for (int j=0; j<vertices[i]->adj.size(); j++) {
            cout << vertices[i]->adj[j].v->num << " ";
        }
        cout << endl;
    }
}

int Maze::findVertexNumFromPosition(int x, int y){
    return y + n*x; 
}

// Creates a default maze of all 1s of size n x n, except for positions (0,0) and (n-1, n-1)
void Maze::createDefaultMaze(){
    cout << "Maze of size (" << n << "x" << n << ")" << endl;
    maze = new int*[n];
    for (int i=0; i<n; i++) {
        int *y = new int[n];
        for (int j=0; j<n; j++) {
            if ((i == 0 && j == 0) || (i == n-1 && j == n-1)) {
                y[i] = 0;
            } else {
                y[j] = 1;
            }
        }
        maze[i] = y;
    }
}

void Maze::createPath(int i, int j){
    maze[i][j] = 0;
}

void Maze::printMaze(){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << "| " << maze[i][j] << " ";
        }
        cout << "|" << endl;
    }
}

vector<int> Maze::findOpenAdjacentPaths(int x, int y){
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<int> neighbors; 
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= n){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= n){
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if(!(i == x && j == y) && maze[i][j] == 0){
                neighbors.push_back(findVertexNumFromPosition(i, j));
            }
        }
    }
    return neighbors;
}

void Maze::convertMazeToAdjacencyListGraph(){
    cout << "Adjacency List Graph:" <<endl;
    for (int x=0; x<n; x++) {
        for (int y=0; y<n; y++) {
            if (maze[x][y] == 0) {
                int num = findVertexNumFromPosition(x,y);
                vector<int> adjacencies = findOpenAdjacentPaths(x,y);
                if (!adjacencies.empty() || (x == 0 && y == 0) ) {
                    addVertex(num);
                }
            }
            
        }
    }

    for (int x=0; x<n; x++) {
        for (int y=0; y<n; y++) {
           if (maze[x][y] == 0) {
               int num = findVertexNumFromPosition(x,y);
               vector<int> adjacencies = findOpenAdjacentPaths(x,y);
               for (int i=0; i<adjacencies.size(); i++) {
                   addEdge(num, adjacencies[i]);
               }
           } 
        }
    }
}

void DFTraversal(vertex *v, vector<int> *p, int n)
{
    cout << "Reached vertex: " << v->num << endl;
    v->visited = true;
    p->push_back(v->num);

    if (v->num == (n*n-1)) {
        return;
    }

    for(int x = 0; x < v->adj.size(); x++ )
    {
        if ((v->adj[x].v->visited == false) && p->back() != (n*n-1)) {
            DFTraversal(v->adj[x].v, p, n);
        }
    }
    if ((p->size() != 1) && p->back() != (n*n-1)) {
        p->pop_back();
        cout << "Backtracked to vertex: " << (*p)[p->size()-1] << endl;
        //DFTraversal(v->adj[v->adj.size()-1].v, p);
    }
}

bool Maze::findPathThroughMaze(){
    cout << "Starting at vertex: 0" << endl;
    //vector<int> *p = &path;
    DFTraversal(vertices[0], &path, n);
    cout << endl;
    return checkIfValidPath();
}


bool Maze::checkIfValidPath(){
    if (path[0] != 0) {
        return false;
    }
    if (path[path.size()-1] != (n*n-1)) {
        return false;
    }
    bool found = false;
    for (int i=1; i<path.size(); i++) {
        found = false;
        int x = path[i] % n;
        int y = path[i] / n;
        vector<int> adjacent = findOpenAdjacentPaths(y,x);
        for (int j=0; j<adjacent.size(); j++) {
           if (adjacent[j] == path[i-1]) {
               found = true;
           }
        }
        if (!found) {return false;}
    }

    return found; 
}

Maze::~Maze(){
    if (n > 0){
        for(int i = 0; i < n; i++){
            delete[] maze[i];
        }
        delete[] maze;
    }
    for (unsigned int i = 0; i< vertices.size(); i++){
        delete vertices[i]; 
    }
}
