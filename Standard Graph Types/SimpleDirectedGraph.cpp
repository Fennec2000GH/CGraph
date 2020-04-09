
#include "SimpleDirectedGraph.h"
using namespace std;

//SimpleDirectedGrapg
//CONSTRUCTORS
template <typename T>
SimpleDirectedGraph<T>::SimpleDirectedGraph():Graph<T>() { }

template <typename T>
SimpleDirectedGraph<T>::SimpleDirectedGraph(string new_title):Graph<T>(new_title) { }

template <typename T>
SimpleDirectedGraph<T>::SimpleDirectedGraph(const SimpleDirectedGraph<T> &other_graph) {

}

//DESTRUCTORS
SimpleDirectedGraph<T>::~SimpleDirectedGraph() { }

//ACCESSORS


//MUTATORS
/* appends new edge to the graph, as long as both endpoints are vertices already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleDirectedGraph<T>::addEdge(Edge<T> &e) {
    try { if(!e.isDirected()) { throw invalid_argument("Edge is not directed!"); } }
    catch (const invalid_argument &error) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    edges.insert(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Appends new edge to the graph, given its endpoints. The endpoints must be already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> SimpleDirectedGraph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {




}

unordered_set<pair<Edge<T>*, bool>> addAllEdges(edge_iterator first, edge_iterator last);
unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);

template <typename T>
pair<Edge<T>*, bool> SimpleDirectedGraph<T>::removeEdge(const Edge<T> &e);

template <typename T>
pair<Edge<T>*, bool> SimpleDirectedGraph<T>::removeEdge(Vertex<T> &v1, Vertex<T> &v2);
void setEdgeWeight(Edge<T> &e, double new_weight);
void setEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2, double new_weight);
void removeEdgeWeight(Edge<T> &e);
void removeEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2);
void addProperty(Property new_property);


