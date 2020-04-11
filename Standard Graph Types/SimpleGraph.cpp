
#include "SimpleGraph.h"
using namespace std;

//SimpleGraph
//CONSTRUCTORS
/* Constructor initializes title to empty string. */
template <typename T>
SimpleGraph<T>::SimpleGraph():Graph<T>() { }

/* Constructor applies new title and implements properties defining the graph. */
template <typename T>
SimpleGraph<T>::SimpleGraph(string new_title):Graph<T>(new_title) { }

/* Copy constructor performs deep copy of another graph. */
template <typename T>
SimpleGraph<T>::SimpleGraph(const SimpleGraph<T> &other_graph):Graph<T>(other_graph) { }

//DESTRUCTORS
/* Destructs graph supposedly, but no dynamic memory is used by the graph. */
template <typename T>
SimpleGraph<T>::~SimpleGraph() { }

//ACCESSORS

//MUTATORS
/* Appends new edge to the graph, as long as both endpoints are vertices already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleGraph<T>::addEdge(Edge<T> &e) {
    //edge case: graph already contains edge
    try { if (containsEdge(e)) { throw invalid_argument("Edge is already present in the graph!"); } }
    catch (const invalid_argument &error) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    //edge case: edge is directed
    try { if(e.isDirected()) { throw invalid_argument("Edge cannot be directed!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    //edge case: edge is weighted
    try { if(e.isWeighted()) { throw invalid_argument("Edge cannot be weighted!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    //edge case: one or both endpoints are not vertices in the graph
    try {
        if(!containsVertex(e.first()) || !containsVertex(e.second())) {
            throw invalid_argument("One or both vertices are not in graph!");
        }
    } catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    //edge case: one or both endpoints has filled full capacity
    try {
        if(e.first().hasCapacity() && getDegree(e.first()) == e.first().getCapacity() ||
            e.second().hasCapacity() && getDegree(e.second()) == e.second().getCapacity())
        { throw logic_error("Capacity for one or both vertices is already filled!"); }
    } catch(const logic_error &error ) {
        error.what();
        return pair<Edge<T> *, bool>(&e, false);
    }

    Graph<T>::edges.insert(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Appends new edge to the graph, given its endpoints. The endpoints must be already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleGraph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {
    //edge case: graph already contains edge
    try { if(containsEdge(v1, v2)) { throw invalid_argument("Edge is already present in the graph!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(nullptr, false);
    }

    //edge case: one or both vertices are not in graph
    try { if(!containsVertex(v1) || !containsVertex(v2)) { throw invalid_argument("One or both vertices are not in graph!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(nullptr, false);
    }

    //edge case: one or both endpoints has filled full capacity
    try {
        if(v1.hasCapacity() && getDegree(v1) == v1.getCapacity() ||
           v2.hasCapacity() && getDegree(v2) == v2.getCapacity())
        { throw logic_error("Capacity for one or both vertices is already filled!"); }
    } catch(const logic_error &error ) {
        error.what();
        return pair<Edge<T>*, bool>(nullptr, false);
    }

    Edge<T> *ptr = new Edge(v1, v2);
    Graph<T>::edges.insert(*ptr);
    return pair<Edge<T>*, bool>(ptr, true);
}

/* Appends all new edges to the graph in the range specified by two (2) iterators. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> SimpleGraph<T>::addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last) {
    unordered_set<pair<Edge<T>&, bool>> output;
    for_each(first, last, [&] (Edge<T> &e) { output.insert(addEdge(e)); } );
    return output;
}

/* Appends all new edges to the graph given in an unordered set. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> SimpleGraph<T>::addAllEdges(const unordered_set<Edge<T>&> edge_set) {
    unordered_set<pair<Edge<T>*, bool>> output;
    for(Edge<T> &e : edge_set) { output.insert(addEdge(e)); }
    return output;
}

/* Appends new property to the graph. */
template <typename T>
void SimpleGraph<T>::addProperty(Property new_property) {
    //edge case: attempt to add invalid property
    try {
        if (allowed_properties.find(new_property) == allowed_properties.end()) {
            throw invalid_argument("Invalid property selected!");
        }
    } catch (const invalid_argument &error ) { error.what(); }

    Graph<T>::properties.insert(new_property);
}

int main() { return 0; }