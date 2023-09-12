#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"

#include <vector>
using std::vector;

class Edge;

class Vertex {
    public:
        int label;
        vector<Edge*> edges;

        // helpers stored inside a vertex to help with path finding
        // you can use different auxilliary structures if desired
        bool visited;
        float distanceTo;
        vector<Vertex*> pathTo;
        Heap<Vertex*>::Locator locator;
        bool operator < ( const Vertex &v ) const { 
            // TODO for locator heap implementation
            return distanceTo < v.distanceTo;
        }

        Vertex (int l) : label (l) { }
};

class Edge {
    public:
        Vertex *v1, *v2;
        float weight;

        Edge (Vertex *nv1, Vertex *nv2, float newWeight) : v1 (nv1), v2 (nv2), weight (newWeight) {}
};

class Graph {
protected:
    vector<Vertex*> v;
    vector<Edge*> e;

public:
    Graph () {}

    // TODO: complete rule of 3
    ~Graph () {
        // TODO
        for (auto i : v) {
            delete i;
        }
        for (auto i : e) {
            delete i;
        }
    }

    Graph (Graph& rhs) {
        if (this != &rhs) {
            for (auto i : rhs.v) {
                this->insertVertex(i->label);
            }
            for (auto i : rhs.e) {
                this->insertEdge(i->v1->label, i->v2->label, i->weight);
            }
        }
    }

    Graph operator=(Graph& rhs) {
        for (auto i : this->v) {
            delete i;
        }
        this->v.clear();
        for (auto i : this->e) {
            delete i;
        }
        this->e.clear();

        for (auto i : rhs.v) {
            this->insertVertex(i->label);
        }
        for (auto i : rhs.e) {
            this->insertEdge(i->v1->label, i->v2->label, i->weight);
        }

        return *this;
    }

    void insertVertex (int label) {
        // TODO
        Vertex* newVert = new Vertex(label);
        v.push_back(newVert);
        newVert->visited = false;
        newVert->distanceTo = INT32_MAX;
        newVert->pathTo.clear();
    }

    void insertEdge ( int l1, int l2, float weight ) {
        // TODO
        Edge* newEdge = new Edge(v[l1], v[l2], weight);
        e.push_back(newEdge);
        v[l1]->edges.push_back(newEdge);
    }

    vector<Vertex*> shortestPath (int start, int end) {
        // TODO: Dijkstra's algorithm
        Heap<Vertex*> heap;

        v[start]->distanceTo = 0;
        v[start]->pathTo.push_back(v[start]);
        v[start]->visited = true;

        for (int i = 0; i < v.size(); i++) {
			v[i]->locator = heap.insertElement(v[i]);
		}

        Vertex* curr;
        while (!heap.isEmpty()) {
            curr = heap.removeMin();
            if (curr->label == end) {
                break;
            }
            for (auto i : curr->edges) {
                if (i->v2->distanceTo > i->weight + i->v1->distanceTo && !i->v2->visited) {
                    i->v2->distanceTo = i->weight + i->v1->distanceTo;
                    i->v2->pathTo = curr->pathTo;
                    i->v2->pathTo.push_back(i->v2);
                    heap.update(i->v2->locator);
                }
            }
        }
        return curr->pathTo;
    }
};
    
#endif