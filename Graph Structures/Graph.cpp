
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
Graph<T>::Graph(string new_title, unordered_set<Property> new_properties): Graph(new_title) { properties = new_properties; }

/* Copy constructor performs deep copy of another graph. */
template <typename T>
Graph<T>::Graph(Graph<T> &other_graph): title(other_graph.title) {
    for(Vertex<T> &v : other_graph.vertices) { vertices.insert(new Vertex(v)); }
    for(Edge<T> &e : other_graph.edges) { edges.insert(new Edge(e)); }
    for(Property p : other_graph.properties) { properties.insert(p); }
}

//DESTRUCTORS
/* Destructs graph supposedly, but no dynamic memory is used by the graph. */
template <typename T>
Graph<T>::~Graph() { }

//ITERATORS
template <typename T>
typename Graph<T>::vertex_iterator Graph<T>::vbegin() { return vertices.begin(); }

template <typename T>
typename Graph<T>::vertex_iterator Graph<T>::vend() { return vertices.end(); }

template <typename T>
typename Graph<T>::const_vertex_iterator Graph<T>::cvbegin() { return vertices.cbegin(); }

template <typename T>
typename Graph<T>::const_vertex_iterator Graph<T>::cvend() { return vertices.cend(); }

template <typename T>
typename Graph<T>::edge_iterator Graph<T>::ebegin() { return  edges.begin(); }

template <typename T>
typename Graph<T>::edge_iterator Graph<T>::eend() { return edges.end(); }

template <typename T>
typename Graph<T>::const_edge_iterator Graph<T>::cebegin() { return edges.cbegin(); }

template <typename T>
typename Graph<T>::const_edge_iterator Graph<T>::ceend() { return edges.cend(); }

//ACCESSORS
/* Gets the title of the graph. */
template <typename T>
string Graph<T>::getTitle() const { return title; }

/* Gets the number of vertices in the graph. */
template <typename T>
size_t Graph<T>::vertexCount() const { return vertices.size(); }

/* Gets the number of edges in the graph. */
template <typename T>
size_t Graph<T>::edgeCount() const { return edges.size(); }

/* Gets the number of edges incident with a vertex, regardless of edge type.*/
template <typename T>
size_t Graph<T>::totalDegree(const Vertex<T> &v) const { return v.degree(); }

/* Gets the difference between the number of outgoing edges and incoming edges at a vertex. For mixed graphs, undirected
 * edges are not considered.
 */
template <typename T>
size_t Graph<T>::netDegree(const Vertex<T> &v) const {
    //edge case: undirected graph
    if(!isDirected()) { throw invalid_argument("Graph is not directed!"); }

    return outDegree(v) - inDegree(v);
}

/* Gets the number of incoming edges at a vertex. For mixed graphs, undirected edges are not considered. */
template <typename T>
size_t Graph<T>::inDegree(const Vertex<T> &v) const {
    //edge case: undirected graph
    if(!isDirected()) { throw invalid_argument("Graph is not directed!"); }

    unordered_set<Edge<T>&> in_edges;
    copy_if(v.neighborhood.cbegin(), v.neighborhood.cend(), in_edges.begin(), [&v](const Edge<T> &e) { return e.first() == v; } );
    return in_edges.size();
}

/* Gets the number of outgoing edges at a vertex. For mixed graphs, undirected edges are not considered. */
template <typename T>
size_t Graph<T>::outDegree(const Vertex<T> &v) const {
    //edge case: undirected graph
    if(!isDirected()) { throw invalid_argument("Graph is not directed!"); }

    unordered_set<Vertex<T>&> out_edges;
    copy_if(v.neighbors.cbegin(), v.neighbors.cend(), out_edges.begin(), [&v](const Edge<T> &e) { return e.second() == v; } );
    return out_edges.size();
}

/* Check for the existence of a given vertex in the graph. */
template <typename T>
bool Graph<T>::containsVertex(const Vertex<T> &v) const { return vertices.count(v) == 1; }

/* Check for the existence of a given edge in the graph. */
template <typename T>
bool Graph<T>::containsEdge(const Edge<T> &e) const { return edges.count(e) == 1; }

/* Check for the existence of a given edge in the graph. Two (2) edges are considered equivalent if the field values in
 * both are the same, and <param>by_content</param> is <code>true</code>.
 */
template <typename T>
bool Graph<T>::containsEdge(const Edge<T> &e, bool by_content) const {
    if(!by_content) { return containsEdge(e); }
    return any_of(
            edges.cbegin(),
            edges.cend(),
            [&e](Edge<T> &r) { return
                (r.v1 == e.v1) &&
                (r.v2 ==e.v2) &&
                (r.directed == e.directed) &&
                (r.weight == e.weight); }
            );
}

/* Check for the existence of a given edge in the graph. The edge must have <param>v1</param> and <param>v2</param>
 * as endpoints.
 */
template <typename T>
bool Graph<T>::containsEdge(const Vertex<T> &v1, const Vertex<T> &v2) const {
    return any_of(
            edges.cbegin(),
            edges.cend(),
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
bool Graph<T>::hasSelfLoops() const { return any_of(edges.cbegin(), edges.cend(), [](const Edge<T> &e) { return e.first() == e.second(); } ); }

/* Checks whether a certain vertex of the graph contains a self-loop. */
template <typename T>
bool Graph<T>::hasSelfLoops(const Vertex<T> &v) const { return any_of(v.neighbors.cbegin(), v.neighbors.cend(), [](const Edge<T> &e) { return e.first() == e.second(); } ); }

/* Gets the edge incident to two (2) vertices. */
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

/* Gets the set of all vertices in the graph. */
template <typename T>
unordered_set<Vertex<T>&> Graph<T>::vertexSet() const { return vertices; }

/* Gets the set of edges in the graph. */
template <typename T>
unordered_set<Edge<T>&> Graph<T>::edgeSet() const { return edges; }

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

/* Appends new vertex to the graph with no edges initially incident to it. */
template <typename T>
pair<Vertex<T>*, bool> Graph<T>::addVertex(const Vertex<T> &new_vertex) {
    //edge case: already exists in graph
    if(containsVertex(new_vertex)) { return pair<Vertex<T>*, bool>(&new_vertex, false); }

    vertices.insert(new_vertex);
    return pair<Vertex<T>*, bool>(&new_vertex, true);
}

/* Remove a vertex from the graph. */
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

/* Appends new edge to the graph, as long as both endpoints are vertices already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> Graph<T>::addEdge(Edge<T> &e) {
    //edge case: one or both endpoints are not vertices in the graph
    if(!containsVertex(e.first()) || !containsVertex(e.second())) { throw invalid_argument("One or both endpoints are not vertices in this graph."); }

    //edge case: edge is already in graph
    if(contains(e) && !isMultigraph()) { return pair<Edge<T>*, bool>(&e, false); }

    edges.insert(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Appends new edge to the graph, given its endpoints. The endpoints must be already present in the graph. */
template <typename T>
pair<Edge<T>*, bool> Graph<T>::addEdge(Vertex<T> &v1, Vertex<T> &v2) {
    //edge case: one or both endpoints are not vertices in the graph
    if(!containsVertex(v1) || !containsVertex(v2)) { throw invalid_argument("One or both endpoints are not vertices in this graph."); }

    //edge case: edge already exists in graph
    if(containsEdge(v1, v2) && !isMultigraph()) { return pair<Edge<T>*, bool>(getEdge(v1, v2), false); }

    edges.insert(new Edge(v1, v2));
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
    if(!containsEdge(e)) { return pair<Edge<T>*, bool>(&e, false); }

    e.first().neighbors.erase(e);
    e.second().neighbors.erase(e);
    edges.erase(e);
    return pair<Edge<T>*, bool>(&e, true);
}

/* Removes and edge from the graph, given its endpoints. */
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

/* Sets new weight on a certain edge in the graph. */
template <typename T>
void Graph<T>::setEdgeWeight(Edge<T> &e, double new_weight) {
    //edge case: the graph does not have the Weighted property
    if(!isWeighted()) { throw logic_error("Graph is not weighted!"); }

    //edge case: edge is not in this graph
    if(!containsEdge(e)) { throw out_of_range("Graph does not contain this edge!"); }

    e.weight = new_weight;
}

/* Sets new weight on a certain edge in the graph, given its endpoints. */
template <typename T>
void Graph<T>::setEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2, double new_weight) {
    //edge case: the graph does not have the Weighted property
    if(!isWeighted()) { throw logic_error("Graph is not weighted!"); }

    //edge case: one or both vertices are not in this graph
    if(!containsVertex(v1) || !containsVertex(v2)) { throw out_of_range("Graph does not contain both vertices!"); }

    Edge<T> &e = getEdge(v1, v2);
    e.weight = new_weight;
}

/* Removes the edge weight of a certain edge, if pre-exists. */
template <typename T>
void Graph<T>::removeEdgeWeight(Edge<T> &e) {
    //edge case: the graph does not have the Weighted property
    if(!isWeighted()) { throw logic_error("Graph is not weighted!"); }

    //edge case: edge is not in this graph
    if(!containsEdge(e)) { throw out_of_range("Graph does not contain this edge!"); }

    e.weight.reset();
}

/* Removes the edge weight of a certain edge, if pre-exists, given its endpoints. */
template <typename T>
void Graph<T>::removeEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2) {
    //edge case: the graph does not have the Weighted property
    if(!isWeighted()) { throw logic_error("Graph is not weighted!"); }

    //edge case: one or both vertices are not in this graph
    if(!containsVertex(v1) || !containsVertex(v2)) { throw out_of_range("Graph does not contain both vertices!"); }

    Edge<T> &e = getEdge(v1, v2);
    e.weight.reset();
}

/* Appends new property to the graph. */
template <typename T>
void Graph<T>::addProperty(Property new_property) { properties.insert(new_property); }

int main() { return 0; }
