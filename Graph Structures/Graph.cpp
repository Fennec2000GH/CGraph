
#include "Graph.h"
using namespace std;

//Graph
//CONSTRUCTORS
template <typename T>
Graph<T>::Graph() { title = ""; }

template <typename T>
Graph<T>::Graph(string new_title): title(new_title) { }

template <typename T>
Graph<T>::Graph(string new_title, unordered_set<Property> new_properties): Graph(new_title) { properties = new_properties; }

template <typename T>
Graph<T>::Graph(Graph<T> &other_graph): title(other_graph.title) {
    for(Vertex<T> &v : other_graph.vertices) { vertices.insert(new Vertex(v)); }
    for(Edge<T> &e : other_graph.edges) { edges.insert(new Edge(e)); }
    for(Property p : other_graph.properties) { properties.insert(p); }
}

//DESTRUCTORS
template <typename T>
Graph<T>::~Graph() { }

//ACCESSORS
template <typename T>
string Graph<T>::getTitle() const { return title; }

template <typename T>
size_t Graph<T>::vertexCount() const { return vertices.size(); }

template <typename T>
size_t Graph<T>::edgeCount() const { return edges.size(); }

template <typename T>
bool Graph<T>::containsVertex(const Vertex<T> &v) const { return vertices.count(v) == 1; }

template <typename T>
bool Graph<T>::containsEdge(const Edge<T> &e) const { return edges.count(e) == 1; }

template <typename T>
bool Graph<T>::containsEdge(const Vertex<T> &v1, const Vertex<T> &v2) const {
    return any_of(
            edges.cbegin(),
            edges.cend(),
            [&v1, &v2](Edge<T> &e){ return (e.first() == v1 && e.second() == v2 || e.first() == v2 && e.second() == v1); });
}

template <typename T>
Edge<T>& Graph<T>::getEdge(const Vertex<T> &v1, const Vertex<T> &v2) const {
    Edge<T> *it = find_if(
            edges.begin(),
            edges.end(),
            [&v1, &v2](Edge<T> &e) { return (e.first() == v1 && e.second() == v2 || e.first() == v2 && e.second() == v1); } );

    //error: such an edge does not exist in graph
    if(it == edges.end()) { throw out_of_range("Such an edge does not exist in graph!"); }

    return *it;
}

template <typename T>
unordered_set<Vertex<T>&> Graph<T>::vertexSet() const { return vertices; }

template <typename T>
unordered_set<Edge<T>&> Graph<T>::edgeSet() const { return edges; }

template <typename T>
unordered_set<Vertex<T>&> Graph<T>::vertexNeighborhood(const Vertex<T> &v) const { return v.vertexNeighborhood(); }

template <typename T>
unordered_set<Edge<T>&> Graph<T>::edgeNeighborhood(const Vertex<T> &v) const { return v.edgeNeighborhood(); }

//MUTATORS
template <typename T>
void Graph<T>::set_title(const string &new_title) { title = new_title; }

template <typename T>
pair<Vertex<T>*, bool> Graph<T>::addVertex(const Vertex<T> &new_vertex) {
    //edge case: already exists in graph
    if(containsVertex(new_vertex)) { return pair<Vertex<T>*, bool>(&new_vertex, false); }

    vertices.insert(new_vertex);
    return pair<Vertex<T>*, bool>(&new_vertex, true);
}

template <typename T>
pair<Vertex<T>*, bool> Graph<T>::removeVertex(Vertex<T> &deleted_vertex) {
    //edge case: no such vertex exists in graph
    if(!containsVertex(deleted_vertex)) { return pair<Vertex<T>*, bool>(deleted_vertex, false); }

    //erasing all edges incident to deleted_vertex
    for(Edge<T> &e : edgeNeighborhood(deleted_vertex)) {
        if(e.first() != deleted_vertex) {
            e.first().neighbors.erase(e);
        } else { e.second().neighbors.erase(e); }
    }

    deleted_vertex.neighbors.clear();
    vertices.erase(deleted_vertex);
    return pair<Vertex<T>*, bool>(deleted_vertex, true);
}

template <typename T>
pair<Edge<T>*, bool> Graph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {
    //edge case: edge already exists in graph
    if(containsEdge(v1, v2)) { return pair<Edge<T>*, bool>(getEdge(v1, v2), false); }

    edges.insert(new Edge(v1, v2));
    return pair<Edge<T>*, bool>(nullptr, true);
}

template <typename T>
pair<Edge<T>*, bool> Graph<T>::removeEdge(const Edge<T> &e) {
    //edge case: edge does not exist in graph
    if(!containsEdge(e)) { return pair<Edge<T>*, bool>(&e, false); }

    e.first().neighbors.erase(e);
    e.second().neighbors.erase(e);
    edges.erase(e);
    return pair<Edge<T>*, bool>(&e, true);
}

template <typename T>
pair<Edge<T>*, bool> Graph<T>::removeEdge(Vertex<T> &v1, Vertex<T> &v2) {
    //edge case: edge does not exist in graph
    if(!containsEdge(v1, v2)) { return pair<Edge<T>*, bool>(nullptr, false); }

    Edge<T> &e = getEdge(v1, v2);
    e.first().neighbors.erase(e);
    e.second().neighbors.erase(e);
    edges.erase(e);
    return pair<Edge<T>*, bool>(e, true);
}

int main() { return 0; }
