
#include "SimpleWeightedGraph.h"
using namespace std;

//SimepleWeightedGraph
//CONSTRUCTORS
/* Constructor initializes title to empty string. */
template <typename T>
SimpleWeightedGraph<T>::SimpleWeightedGraph():Graph<T>() { addProperty(Property::WeightedEdges); }

/* Constructor applies new title and implements properties defining the graph. */
template <typename T>
SimpleWeightedGraph<T>::SimpleWeightedGraph(string new_title):Graph<T>(new_title) { addProperty(Property::WeightedEdges); }

/* Copy constructor performs deep copy of another graph. */
template <typename T>
SimpleWeightedGraph<T>::SimpleWeightedGraph(const SimpleWeightedGraph<T> &other_graph):Graph<T>(other_graph) { }

//DESTRUCTORS
/* Destructs graph supposedly, but no dynamic memory is used by the graph. */
template <typename T>
SimpleWeightedGraph<T>::~SimpleWeightedGraph() { }

//ACCESSORS

//MUTATORS
/* Appends new edge to the graph, as long as both endpoints are vertices already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleWeightedGraph<T>::addEdge(Edge<T> &e) {
    //edge case: graph already contains edge
    try { if (containsEdge(e)) { throw invalid_argument("Edge is already present in the graph!"); } }
    catch (const invalid_argument &error) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    Graph<T>::edges.insert(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Appends new edge to the graph, given its endpoints. The endpoints must be already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleWeightedGraph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {
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

if(containsVertex(v1))
Graph<T>::edges.insert(new Edge(v1, v2));
}

/* Appends all new edges to the graph in the range specified by two (2) iterators. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> SimpleWeightedGraph<T>::addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last) {
    unordered_set<pair<Edge<T>&, bool>> output;
    for_each(first, last, [&] (Edge<T> &e) { output.insert(addEdge(e)); } );
    return output;
}

/* Appends all new edges to the graph given in an unordered set. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> SimpleWeightedGraph<T>::addAllEdges(const unordered_set<Edge<T>&> edge_set) {
unordered_set<pair<Edge<T>*, bool>> output;
for(Edge<T> &e : edge_set) { output.insert(addEdge(&e)); }
return output;
}

//template <typename T>
//pair<Edge<T>*, bool> SimpleWeightedGraph<T>::removeEdge(Vertex<T> &v1, Vertex<T> &v2);

/* Sets new weight on a certain edge in the graph. */
template <typename T>
void setEdgeWeight(Edge<T> &e, double new_weight) {
//graph is unweighted, so this function is useless
try { throw logic_error("Graph is unweighted!"); }
catch (const logic_error &error ) { error.what(); }
}

/* Sets new weight on a certain edge in the graph, given its endpoints. */
template <typename T>
void SimpleWeightedGraph<T>::setEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2, double new_weight) {
    //graph is unweighted, so this function is useless
    try { throw logic_error("Graph is unweighted!"); }
    catch (const logic_error &error ) { error.what(); }
}

/* Removes the edge weight of a certain edge, if pre-exists. */
template <typename T>
void SimpleWeightedGraph<T>::removeEdgeWeight(Edge<T> &e) {
    //graph is unweighted, so this function is useless
    try { throw logic_error("Graph is unweighted!"); }
    catch (const logic_error &error ) { error.what(); }
}

/* Removes the edge weight of a certain edge, if pre-exists, given its endpoints. */
template <typename T>
void SimpleWeightedGraph<T>::removeEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2) {
    //graph is unweighted, so this function is useless
    try { throw logic_error("Graph is unweighted!"); }
    catch (const logic_error &error ) { error.what(); }
}

/* Appends new property to the graph. */
template <typename T>
void SimpleWeightedGraph<T>::addProperty(Property new_property) {
    //edge case: attempt to add invalid property
    try {
        if (allowed_properties.find(new_property) == allowed_properties.end()) {
            throw invalid_argument("Invalid property selected!");
        }
    } catch (const invalid_argument &error ) { error.what(); }

    Graph<T>::properties.insert(new_property);
}

int main() { return 0; }
