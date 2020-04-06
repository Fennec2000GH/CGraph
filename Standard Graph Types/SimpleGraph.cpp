
#include "SimpleGraph.h"
using namespace std;

//SimpleGraph
//CONSTRUCTORS
template <typename T>
SimpleGraph<T>::SimpleGraph():Graph<T>() { }

template <typename T>
SimpleGraph<T>::SimpleGraph(string new_title):Graph<T>(new_title) { }

template <typename T>
SimpleGraph<T>::SimpleGraph(const SimpleGraph<T> &other_graph):Graph<T>(other_graph) { }

//DESTRUCTORS
template <typename T>
SimpleGraph<T>::~SimpleGraph() { }

//ACCESSORS

//MUTATORS
/* Appends new edge to the graph, as long as both endpoints are vertices already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleGraph<T>::addEdge(Edge<T> &e) {
    //edge case: graph already contains edge
    if(containsEdge(e)) { throw invalid_argument("Edge is already present in the graph!"); }
    Graph<T>::edges.insert(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Appends new edge to the graph, given its endpoints. The endpoints must be already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleGraph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {
    //edge case: graph already contains edge
    if(containsEdge(v1, v2)) { throw invalid_argument("Edge is already present in the graph!"); }
    Graph<T>::edges.insert(new Edge(v1, v2));
}

/* Appends all new edges to the graph in the range specified by two (2) iterators. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> SimpleGraph<T>::addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last) {
    unordered_set<pair<Edge<T>&, bool>> output;
    for_each(
            first,
            last,
            [&] (Edge<T> &e) {
                if(containsEdge(e)) { output.insert(pair<Edge<T>*, bool>(&e, false)); }
                else {
                    Graph<T>::edges.insert(e);
                    output.insert(pair<Edge<T>*, bool>(&e, true));
                }
            });
    return output;
}

/* Appends all new edges to the graph given in an unordered set. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> SimpleGraph<T>::addAllEdges(const unordered_set<Edge<T>&> edge_set) {
    unordered_set<pair<Edge<T>*, bool>> output;
    for(Edge<T> &e : edge_set) { output.insert(addEdge(&e)); }
    return output;
}

/* Appends new property to the graph. */
template <typename T>
void SimpleGraph<T>::addProperty(Property new_property) {
    if(allowed_properties.find(new_property) != allowed_properties.end()) {
        Graph<T>::properties.insert(new_property);
    }
}

int main() { return 0; }