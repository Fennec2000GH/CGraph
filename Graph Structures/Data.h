
#pragma once
#include "Graph.h"
#include <bitset>
#include <unordered_map>
#include <vector>
using namespace std;

#ifndef CGRAPH_GRAPHFORM_H
#define CGRAPH_GRAPHFORM_H

template <typename T = int>
class Data {
public:
    //CONSTRUCTORS
    Data();

    //DESTRUCTORS
    virtual ~Data();

    //ACCESSORS
    virtual size_t size() const = 0;

};

template <typename T = int>
class AdjacencyList : public Data<T> {
public:
    //CONSTRUCTOR
    AdjacencyList();
    AdjacencyList(Graph<T> &new_graph);

    //DESTRUCTORS
    ~AdjacencyList();

    //ACCESSORS
    size_t size() const;
    unsorted_set<unsigned> neighborhoodSizes() const;

    //MUTATORS
    void setGraph(Graph<T> &new_graph);

    //ITERATORS
    unordered_set<Vertex<T>&>::iterator& begin();
    unordered_set<Vertex<T>&>::iterator& end();
    unordered_set<Vertex<T>&>::const_iterator cbegin() const;
    unordered_set<Vertex<T>&>::const_iterator cend() const;

private:
    unsorted_map<Vertex<T>&, unsorted_set<Vertex<T>&>> adj_list;

};

template <typename T>
class AdjacencyMatrix : public Data<T> {
public:
    //CONSTRUCTORS
    AdjacencyMatrix();
    AdjacencyMatrix(Graph<T> &new_graph);

    //DESTRUCTORS
    ~AdjacencyMatrix();

    //ACCESSORS
    size_t size() const;

    //MUTATORS
    void setGraph(Graph<T> &new_graph);

private:
    size_t vertex_size; //number of vertices, therefore actual meaningful row and column dimension in adjacency matrix
    vector<vector<T>> adj_matrix;

}

#endif //CGRAPH_GRAPHFORM_H
