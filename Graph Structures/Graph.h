
#include <bitset>
#include <iostream>
#include <iterator>
#include <tuple>
#include <unordered_set>
using namespace std;

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H

enum Property { SelfLoop, WeightedEdges, MultipleEdges, DirectedEdges };
template <typename T = int>
class Graph {
public:
    //CONSTRUCTORS
    Graph();
    Graph(string new_title);
    Graph(string new_title, unordered_set<Property> new_properties);

    //ACCESSORS
    string title() const;
    size_t vertexCount() const;
    size_t edgeCount() const;
    &unordered_set<Node<T>*> vertexSet() const;
    unordered_set<tuple<Node<T>*, Node<T>*, optional<bool>>& edgeSet() const;

    //MUTATORS
    void set_title(string new_title);
    pair<Node<T>*, bool> addVertex(Node<T> &node);
    pair<Node<T>*, bool> removeVertex(Node<T> &node);
    pair<Node<T>*, bool> addEdge(Node<T> &node1, Node<T> &node2);
    pair<Node<T>*, bool> removeEdge(Node<T> &node1, Node<T> &node2);

private:
    //MEMBER VARIABLES
    string title;
    unordered_set<Node<T>*> vertices;
    unordered_set<tuple<Node<T>*, Node<T>*, optional<int>, optional<bool>> edges;
    unordered_set<Property> properties;

};


#endif //CGRAPH_GRAPH_H
