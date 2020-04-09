
#include "../Graph Structures/Graph.h"
using namespace std;

#ifndef CGRAPH_MULTIGRAPH_H
#define CGRAPH_MULTIGRAPH_H

template <typename T>
class Multigraph : public Graph<T> {
public:
    //CONSTRUCTORS
    Multigraph();
    Multigraph(string new_title);
    Multigraph(const Multigraph<T> &other_graph);

    //DESTRUCTORS
    ~Multigraph();

    //ACCESSORS

    //MUTATORS
    pair<Edge<T>*, bool> addEdge(Edge<T> &e);
    pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);
    void addProperty(Property new_property);


private:
    //MEMBER VARIABLES
    unordered_set<Property> allowed_properties = {Property::Cycleless, Property::Unmodifiabled, Property::MultipleEdges};

};

#endif //CGRAPH_MULTIGRAPH_H
