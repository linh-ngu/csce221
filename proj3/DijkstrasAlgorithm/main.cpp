#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char * argv[]) {
    cout << "Filename of graph to load: ";

    // TODO: next five code snippets
    // Snippet 1: read filename and open file

    string filename;
    cin >> filename;
    ifstream fin(filename);

    // Snippet 2: get number graph size

    int numVert;
    int numEdge;

    fin >> numVert;
    fin >> numEdge;

    // Snippet 3: create graph

    Graph graph;
    for (int i = 0; i < numVert; i++) {
        graph.insertVertex(i);
    }

    // Snippet 4: read edges

    int vert1;
    int vert2;
    float weight;

    for (int i = 0; i < numEdge; i++) {
        fin >> vert1;
        fin >> vert2;
        fin >> weight;
        graph.insertEdge(vert1, vert2, weight);
        graph.insertEdge(vert2, vert1, weight);
    }

    // Snippet 5: read start and end of path

    int startVertex;
    int endVertex;

    fin >> startVertex;
    fin >> endVertex;

    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;

    vector<Vertex*> path;

    // TODO: call shortest path on your graph for the start and end vertices and save result to path

    path = graph.shortestPath(startVertex, endVertex);
    
    for (auto i : path) { // this is a for-each loop
        cout << i->label << " ";
    }
    // cout endline at very end
    cout << endl;
    return 0;
}