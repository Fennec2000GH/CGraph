
#include "Multigraph.h"
using namespace std;

//Multigraph
//CONSTRUCTORS
/* Constructor initializes title to empty string. */
template <typename T>
Multigraph<T>::Multigraph():Graph<T>() { addProperty(Property::MultipleEdges); }

/* Constructor applies new title and implements properties defining the graph. */
template <typename T>
Multigraph<T>::Multigraph(string new_title):Graph<T>(new_title) { addProperty(Property::MultipleEdges); }

/* Copy constructor performs deep copy of another graph. */
template <typename T>
Multigraph<T>::Multigraph(const Multigraph<T> &other_graph):Graph<T>(other_graph) { }

//DESTRUCTORS
/* Destructs graph supposedly, but no dynamic memory is used by the graph. */
template <typename T>
Multigraph<T>::~Multigraph() { }

//ACCESSORS
/* Count the number of times an edge exists between the same two (2) endpoints, given an edge */
template <typename T>
unsigned Multigraph<T>::getEdgeDuplicity(const Edge<T> &e) const {
    //edge case: graph does not contain edge
    try { if (!containsEdge(e)) { throw invalid_argument("Edge is not in graph!"); } }
    catch (const invalid_argument &error) {
        error.what();
        return -1;
    }

    return getEdgeDuplicity(e.first(), e.second());
}

/* Count the number of times an edge exists between the same two (2) endpoints, given the endpoints */
template <typename T>
unsigned Multigraph<T>::getEdgeDuplicity(const Vertex<T> &v1, const Vertex<T> &v2) const {
    //edge case: one or both vertices are not in graph
    try { if(!containsVertex(v1) || !containsVertex(v2)) { throw invalid_argument("One or both vertices are not in graph!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return -1;
    }

    return ( edges.find(pair<Vertex<T>&, Vertex<T>&>(v1, v2)) == edges.end() ?
    edges[pair<Vertex<T>&, Vertex<T>&>(v1, v2)].size() :
    edges[pair<Vertex<T>&, Vertex<T>&>(v2, v1)].size() );
}

/* Get the degree of a vertex as if each set of duplicate edges is flattened into a single edge */
template <typename T>
unsigned Multigraph<T>::getUniqueDegree(const Vertex<T> &v) const {
    return count_if(Graph<T>::cebegin(), Graph<T>::ceend(), [&v] (const Edge<T> &e) { return e.first() == v || e.second() == v; } );
}

//MUTATORS
/* Appends new edge to the graph, as long as both endpoints are vertices already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> Multigraph<T>::addEdge(Edge<T> &e) {
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

    //adding edge to multigraph edge map
    pair<Vertex<T>&, Vertex<T>&> target_key = pair<Vertex<T>&, Vertex<T>&>(min(e.first(), e.second()), max(e.first(), e.second()));
    if(Multigraph<T>::edges.find(target_key) != Multigraph<T>::edges.end()) {
        Multigraph<T>::edges[target_key].push_back(e);
    } else if(e.first() == e.second() &&
                Multigraph<T>::edges.find(pair<Vertex<T>&, Vertex<T>&>(e.second(), e.first())) != Multigraph<T>::edge.end()) {
        Multigraph<T>::edges[pair<Vertex<T>&, Vertex<T>&>(e.second(), e.first())].push_back(e);
    } else {
        Multigraph<T>::edges.try_emplace(target_key, {e});
    }

    Graph<T>::edges.insert(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Appends new edge to the graph, given its endpoints. The endpoints must be already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> Multigraph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {
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

    //adding edge to multigraph edge map
    pair<Vertex<T>&, Vertex<T>&> target_key = pair<Vertex<T>&, Vertex<T>&>(min(v1, v2), max(v1, v2));
    if(Multigraph<T>::edges.find(target_key) != Multigraph<T>::edges.end()) {
        Multigraph<T>::edges[target_key].push_back(*ptr);
    } else if(v1 == v2 && Multigraph<T>::edges.find(pair<Vertex<T>&, Vertex<T>&>(v2, v1)) != Multigraph<T>::edge.end()) {
        Multigraph<T>::edges[pair<Vertex<T>&, Vertex<T>&>(v2, v1)].push_back(*ptr);
    } else {
        Multigraph<T>::edges.try_emplace(target_key, {*ptr});
    }
    Graph<T>::edges.insert(*ptr);
    return pair<Edge<T>*, bool>(ptr, true);
}

/* Appends all new edges to the graph in the range specified by two (2) iterators. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> Multigraph<T>::addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last) {
    unordered_set<pair<Edge<T>&, bool>> output;
    for_each(first, last, [&] (Edge<T> &e) { output.insert(addEdge(e)); } );
    return output;
}

/* Appends all new edges to the graph given in an unordered set. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> Multigraph<T>::addAllEdges(const unordered_set<Edge<T>&> edge_set) {
    unordered_set<pair<Edge<T>*, bool>> output;
    for(Edge<T> &e : edge_set) { output.insert(addEdge(&e)); }
    return output;
}

/* Appends new property to the graph. */
template <typename T>
void Multigraph<T>::addProperty(Property new_property) {
    //edge case: attempt to add invalid property
    try {
        if (allowed_properties.find(new_property) == allowed_properties.end()) {
            throw invalid_argument("Invalid property selected!");
        }
    } catch (const invalid_argument &error ) { error.what(); }

    Graph<T>::properties.insert(new_property);
}
int main() { return 0; }
