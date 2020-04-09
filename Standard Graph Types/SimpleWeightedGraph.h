
#include "../Graph Structures/Graph.h"
using namespace std;

#ifndef CGRAPH_SIMPLEWEIGHTEDGRAPH_H
#define CGRAPH_SIMPLEWEIGHTEDGRAPH_H

template <typename T>
class SimpleWeightedGraph : public Graph<T> {
public:
    //CONSTRUCTORS
    SimpleWeightedGraph();
    SimpleWeightedGraph(string new_title);
    SimpleWeightedGraph(const SimpleWeightedGraph<T> &other_graph);

    //DESTRUCTORS
    ~SimpleWeightedGraph();

    //ACCESSORS

    //MUTATORS
    pair<Edge<T>*, bool> addEdge(Edge<T> &e);
    pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);
    void setEdgeWeight(Edge<T> &e, double new_weight);
    void setEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2, double new_weight);
    void removeEdgeWeight(Edge<T> &e);
    void removeEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2);
    void addProperty(Property new_property);

private:
    //MEMBER VARIABLES
    unordered_set<Property> allowed_properties = {Property::Cycleless, Property::Unmodifiable, Property::WeightedEdges};

};


#endif //CGRAPH_SIMPLEWEIGHTEDGRAPH_H
