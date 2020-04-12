
#include "Pseudograph.h"
using namespace std;

//CONSTRUCTORS


//DESTRUCTORS

//ACCESSORS
template <typename T>
unsigned getDegree(const Vertex<T> &v) const {
    //edge case: one or both endpoints are not vertices in the graph
    try { if(!containsVertex(v)) { throw invalid_argument("Vertex is not in graph!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return -1;
    }

    //finding number of incident edges that are no self-loops
    unsigned non_loop_edges = count_if(Graph<T>::cebegin(), Graph<T>::ceend(), [&v] (const Edge<T> &e) {
        return e.first() == 
    })

    unsigned

}

template <typename T>
unsigned getSelfLoopDensity() const {


}

template <typename T>
bool hasSelfLoop(const Vertex<T> &v) const {


}


//MUTATORS

