
#include "Pseudograph.h"
using namespace std;

//CONSTRUCTORS
template <typename>
Pseudograph<T>::Pseudograph():Multigraph<T>() { }

template <typename>
Pseudograph<T>::Pseudograph(string new_title):Multigraph<T>(new_title) { }

template <typename>
Pseudograph<T>::Pseudograph(const Pseudograph<T> &other_graph):Multigraph<T>(other_graph) { }

//DESTRUCTORS

//ACCESSORS

template <typename T>
unsigned Pseudograph<T>::getDegree(const Vertex<T> &v) const {
    //edge case: one or both endpoints are not vertices in the graph
    try { if(!containsVertex(v)) { throw invalid_argument("Vertex is not in graph!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return -1;
    }

    unsigned degree = 0;
    Edge<T> temp_edge;
    for(auto it = Multigraph<T>::edges.cbegin(); it != Multigraph<T>::edges.cend(); it++) {
        temp_edge = new Edge<T>(it -> first -> first, it -> first -> second);
        if(temp_edge.first == v || temp_edge.second == v) {
            //check for self-loop
            degree += temp_edge.isSelfLoop() ? 2 : 1;
        }
    }

    return degree;
}

/* Computes the frequency of occurrence of a self-loop */
template <typename T>
double Pseudograph<T>::getSelfLoopDensity() const {
    unsigned num_loops = accumulate(Pseudograph<T>::self_loop_edges.cbegin(), Pseudograph<T>::self_loop_edges.cend(), 0,
                        [] (unsigned a, const pair<Vertex<T>&, unsigned> &p) { return a + p.second; } );
    unsigned num_edges = Graph<T>::edgeCount();
    return (double)num_loops / num_edges;
}

/* Check whether vertex is a self-loop */
template <typename T>
bool Pseudograph<T>::hasSelfLoop(const Vertex<T> &v) const {
    //edge case: vertex is not in graph
    if(!containsVertex(v)) { throw invalid_argument("Vertex is not in graph!");
    return find_if(Pseudograph<T>::self_loop_edges.cbegin(), Pseudograph<T>::self_loop_edges.cend(),
            [] (const pair<Vertex<T> &p) { return p.first == v; } ) != Pseudograph<T>::self_loop_edges.cend();
}


//MUTATORS

