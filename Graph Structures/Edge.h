
#pragma once
#include "Node.h"
#include <iostream>
#include <optional>
using namespace std;

#ifndef CGRAPH_EDGE_H
#define CGRAPH_EDGE_H

//FORWARD DECLARATION
template <typename T>
class Node;

template <typename T = int>
class Edge {
friend class Graph;

public:
    //CONSTRUCTORS
    Edge(Node<T> &new_node1, Node<T> &new_node2);
    Edge(Node<T> &new_node1, Node<T> &new_node2, bool new_directed);
    Edge(Node<T> &new_node1, Node<T> &new_node2, bool new_directed, double new_weight);

    //ACCESSORS
    Node<T>& first() const;
    Node<T>& second() const;
    bool isDirected() const;
    bool isWeighted() const;
    bool getWeight() const;

private:
    //MUTATORS
    void setFirst(Node<T> &new_node1);
    void setSecond(Node<T> &new_node2);
    void setDirected(bool new_directed);
    void setWeight(double new_weight);

    //MEMBER VARIABLES
    Node<T> &node1;
    Node<T> &node2;
    bool directed;
    optional<double> weight;

};


#endif //CGRAPH_EDGE_H
