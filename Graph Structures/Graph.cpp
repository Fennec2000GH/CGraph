
#include "Graph.h"
using namespace std;

//Graph
//CONSTRUCTORS
/* Constructor initializes title to empty string. */
template <typename T>
Graph<T>::Graph() { title = ""; }

/* Constructor applies new title. */
template <typename T>
Graph<T>::Graph(string new_title): title(new_title) { }

/* Constructor applies new title and implements properties defining the graph. */
template <typename T>
Graph<T>::Graph(string new_title, unordered_set<Property> new_properties): Graph(new_title) { Graph<T>::properties = new_properties; }

/* Copy constructor performs deep copy of another graph. */
template <typename T>
Graph<T>::Graph(Graph<T> &other_graph): title(other_graph.title) {
    vertices.clear();
    for(Vertex<T> &v : other_graph.vertices) { Graph<T>::vertices.insert(new Vertex(v)); }

    Graph<T>::edges.clear();
    for(Edge<T> &e : other_graph.edges) { Graph<T>::edges.insert(new Edge(e)); }

    properties.clear();
    for(Property p : other_graph.properties) { Graph<T>::properties.insert(p); }
}

//DESTRUCTORS
/* Destructs graph supposedly, but no dynamic memory is used by the graph. */
template <typename T>
Graph<T>::~Graph() { }

//ITERATORS
template <typename T>
typename Graph<T>::vertex_iterator Graph<T>::vbegin() { return Graph<T>::vertices.begin(); }

template <typename T>
typename Graph<T>::vertex_iterator Graph<T>::vend() { return Graph<T>::vertices.end(); }

template <typename T>
typename Graph<T>::const_vertex_iterator Graph<T>::cvbegin() { return Graph<T>::vertices.cbegin(); }

template <typename T>
typename Graph<T>::const_vertex_iterator Graph<T>::cvend() { return Graph<T>::vertices.cend(); }

template <typename T>
typename Graph<T>::edge_iterator Graph<T>::ebegin() { return Graph<T>::edges.begin(); }

template <typename T>
typename Graph<T>::edge_iterator Graph<T>::eend() { return Graph<T>::edges.end(); }

template <typename T>
typename Graph<T>::const_edge_iterator Graph<T>::cebegin() { return Graph<T>::edges.cbegin(); }

template <typename T>
typename Graph<T>::const_edge_iterator Graph<T>::ceend() { return Graph<T>::edges.cend(); }

//ACCESSORS
/* Gets the title of the graph. */
template <typename T>
string Graph<T>::getTitle() const { return title; }

/* Gets the number of vertices in the graph. */
template <typename T>
unsigned Graph<T>::vertexCount() const { return vertices.size(); }

/* Gets the number of edges in the graph. */
template <typename T>
unsigned Graph<T>::edgeCount() const { return Graph<T>::edges.size(); }

/* Gets the number of edges incident with a vertex, regardless of edge type.*/
template <typename T>
unsigned Graph<T>::getDegree(const Vertex<T> &v) const {
    return count_if(cebegin(), ceend(), [&v](const Edge<T> &e) { return e.first() == v || e.second() == v; } );
}

/* Check for the existence of a given vertex in the graph. */
template <typename T>
bool Graph<T>::containsVertex(const Vertex<T> &v) const { return vertices.count(v) == 1; }

/* Check for the existence of a given edge in the graph. */
template <typename T>
bool Graph<T>::containsEdge(const Edge<T> &e) const { return Graph<T>::edges.count(e) == 1; }

/* Check for the existence of a given edge that has endpoints equivalent to the endpoints of given edge by content and
 * also has matching edge field values.
 */
template <typename T>
bool Graph<T>::containsMatchingEdge(const Edge<T> &e) const {
    return any_of(
            cebegin(),
            ceend(),
            [&e](Edge<T> &r) { return
                (r.v1.equals(e.v1)) &&
                (r.v2.equals(e.v2)) &&
                (r.directed == e.directed) &&
                (r.weight == e.weight);
            });
}

/* Check for the existence of a given edge in the graph. The edge must have <param>v1</param> and <param>v2</param>
 * as endpoints.
 */
template <typename T>
bool Graph<T>::containsEdge(const Vertex<T> &v1, const Vertex<T> &v2) const {
    return any_of(
            cebegin(),
            ceend(),
            [&v1, &v2](Edge<T> &e) { return (e.first() == v1 && e.second() == v2 || e.first() == v2 && e.second() == v1); });
}

/* Checks whether the graph is undirected. */
template <typename T>
bool Graph<T>::isUndirected() const { return properties.find(Property::DirectedEdges) == properties.end(); }

/* Checks whether the graph is directed. */
template <typename T>
bool Graph<T>::isDirected() const { return properties.find(Property::DirectedEdges) != properties.end(); }

/* Checks whether the graph is unweighted on its edges. */
template <typename T>
bool Graph<T>::isUnweighted() const { return properties.find(Property::WeightedEdges) == properties.end(); }

/* Checks whether the graph is weighted on its edges. */
template <typename T>
bool Graph<T>::isWeighted() const { return properties.find(Property::WeightedEdges) != properties.end();}

/* Checks whether the graph has both undirected and directed edges. */
template <typename T>
bool Graph<T>::isMixed() const { return properties.find(Property::MixedEdges) != properties.end(); }

/* Checks whether the graph can be modified. */
template <typename T>
bool Graph<T>::isModifiable() const { return properties.find(Property::Unmodifiable) == properties.end(); }

/* Checkes whether the graph allows multiple edges per pair of vertices. */
template <typename T>
bool Graph<T>::isMultigraph() const { return properties.find(Property::MultipleEdges) != properties.end(); }

/* Checks whether the graph is a pseudograph. */
template <typename T>
bool Graph<T>::isPseudograph() const { return isMultigraph() && allowsSelfLoops(); }

/* Checks whether the graph has at most a single, undirected, and unweighted edge between any pair of vertices and also
 * no self-loops.
 */
template <typename T>
bool Graph<T>::isSimple() const {
    if(allowsSelfLoops() || isDirected() || isMixed() || isMultigraph() || isWeighted()) { return false; }
    return true;
}

/* Checks whether the graph can have self-loops. */
template <typename T>
bool Graph<T>::allowsSelfLoops() const { return properties.find(Property::SelfLoops) != properties.end(); }

/* Checks whether the graph actually contains any self-loops. */
template <typename T>
bool Graph<T>::hasSelfLoops() const { return any_of(cebegin(), ceend(), [](const Edge<T> &e) { return e.first() == e.second(); } ); }

/* Checks whether a certain vertex of the graph contains a self-loop. */
template <typename T>
bool Graph<T>::hasSelfLoops(const Vertex<T> &v) const { return any_of(v.neighbors.cbegin(), v.neighbors.cend(), [](const Edge<T> &e) { return e.first() == e.second(); } ); }

/* Gets the edge incident to two (2) vertices. */
template <typename T>
Edge<T>& Graph<T>::getEdge(const Vertex<T> &v1, const Vertex<T> &v2) const {
    Edge<T> *it = find_if(
            cebegin(),
            ceend(),
            [&v1, &v2](Edge<T> &e) { return (e.first() == v1 && e.second() == v2 || e.first() == v2 && e.second() == v1); } );

    //error: such an edge does not exist in graph
    if(it == ceend()) { throw out_of_range("Such an edge does not exist in graph!"); }

    return *it;
}

/* Gets the set of all vertices in the graph. */
template <typename T>
unordered_set<Vertex<T>&> Graph<T>::vertexSet() const { return Graph<T>::vertices; }

/* Gets the set of edges in the graph. */
template <typename T>
unordered_set<Edge<T>&> Graph<T>::edgeSet() const { return Graph<T>::edges; }

/* Gets the set of all adjacent vertices to a certain vertex in the graph. */
template <typename T>
unordered_set<Vertex<T>&> Graph<T>::vertexNeighborhood(const Vertex<T> &v) const {
    //edge case: vertex is not in this graph
    if(!containsVertex(v)) { throw invalid_argument("Vertex is not in this graph!"); }
    return v.vertexNeighborhood();
}

/* Gets the set of all adjacent edges incident to a certain vertex in the graph. */
template <typename T>
unordered_set<Edge<T>&> Graph<T>::edgeNeighborhood(const Vertex<T> &v) const {
    //edge case: vertex is not in this graph
    if(!containsVertex(v)) { throw invalid_argument("Vertex is not in this graph!"); }
    return v.edgeNeighborhood();
}

//MUTATORS
/* Sets new title for the graph. */
template <typename T>
void Graph<T>::set_title(const string &new_title) { title = new_title; }

/* Creates a new vertex with no incident edges and appends to graph */
template <typename T>
pair<Vertex<T>*, bool> Graph<T>::addVertex() { return vertices.insert(new Vertex<T>()); }

/* Appends new vertex to the graph with no edges initially incident to it. */
template <typename T>
pair<Vertex<T>*, bool> Graph<T>::addVertex(const Vertex<T> &new_vertex) {
    //edge case: already exists in graph
    try { if(containsVertex(new_vertex)) { throw invalid_argument("Graph already contains vertex!"); } }
    catch(const invalid_argument &error) {
        error.what();
        return pair<Vertex<T>*, bool>(&new_vertex, false);
    }

    //removing any attached edges, if exists
    new_vertex.neighbors.clear();

    vertices.insert(new_vertex);
    return pair<Vertex<T>*, bool>(&new_vertex, true);
}

/* Remove a vertex from the graph. */
template <typename T>
pair<Vertex<T>*, bool> Graph<T>::removeVertex(Vertex<T> &deleted_vertex) {
    //edge case: no such vertex exists in graph
    try { if(!containsVertex(deleted_vertex)) { throw invalid_argument("Graph does not contain such a vertex!"); } }
    catch(const invalid_argument &error) {
        error.what();
        return pair<Vertex<T>*, bool>(&deleted_vertex, false);
    }

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

/* Appends new edge to the graph, as long as both endpoints are vertices already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> Graph<T>::addEdge(const Edge<T> &e) {
    //edge case: one or both endpoints are not vertices in the graph
    try {
        if(!containsVertex(e.first()) || !containsVertex(e.second())) {
            throw invalid_argument("One or both vertices are not in graph!");
        }
    } catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    //edge case: edge is already in graph
    try { if (contains(e)) { throw invalid_argument("Edge is duplicate and graph does not allow multiple edges!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(&e, false);
    }

    Graph<T>::edges.insert(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Appends new edge to the graph, given its endpoints. The endpoints must be already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> Graph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {
    //edge case: one or both endpoints are not vertices in the graph
    try {
        if (!containsVertex(v1) || !containsVertex(v2)) {
            throw invalid_argument("One or both vertices are not in graph!");
        }
    } catch (const invalid_argument &error ){
        error.what();
        return pair<Edge<T>*, bool>(nullptr, false);
    }

    //edge case: edge already exists in graph
    try { if(containsEdge(v1, v2)) { throw invalid_argument("Edge is already in graph!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(getEdge(v1, v2), false);
    }

    Graph<T>::edges.insert(new Edge(v1, v2));
    return pair<Edge<T>*, bool>(nullptr, true);
}

/* Appends all new edges to the graph in the range specified by two (2) iterators. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> Graph<T>::addAllEdges(edge_iterator it1, edge_iterator it2) {
    unordered_set<pair<Edge<T>*, bool>> output;
    for(auto it = it1; it != it2 && it != nullptr; it++) { output.insert(addEdge(*it)); }
    return output;
}

/* Appends all new edges to the graph given in an unordered set. The endpoints for each edge must be
 * already present in the graph.
 */
template <typename T>
unordered_set<pair<Edge<T>*, bool>> Graph<T>::addAllEdges(const unordered_set<Edge<T>&> edge_set) {
    unordered_set<pair<Edge<T>*, bool>> output;
    for(Edge<T> &e : edge_set) { output.insert(addEdge(e));}
    return output;
}

/* Removes an edge from the graph. */
template <typename T>
pair<Edge<T>*, bool> Graph<T>::removeEdge(const Edge<T> &e) {
    //edge case: edge does not exist in graph
    try { if (!containsEdge(e)) { throw invalid_argument("Graph does not contain such an edge!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T> *, bool>(&e, false);
    }

    e.first().neighbors.erase(e);
    e.second().neighbors.erase(e);
    Graph<T>::edges.erase(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Removes and edge from the graph, given its endpoints. */
template <typename T>
pair<Edge<T>*, bool> Graph<T>::removeEdge(Vertex<T> &v1, Vertex<T> &v2) {
    //edge case: edge does not exist in graph
    try { if(!containsEdge(v1, v2)) { throw invalid_argument("Graph does not contain such an edge!"); } }
    catch (const invalid_argument &error ) {
        error.what();
        return pair<Edge<T>*, bool>(nullptr, false);
    }

    Edge<T> &e = getEdge(v1, v2);
    e.first().neighbors.erase(e);
    e.second().neighbors.erase(e);
    Graph<T>::edges.erase(e);
    return pair<Edge<T>*, bool>(e, true);
}

int main() { return 0; }
