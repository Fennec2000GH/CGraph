
#include "Data.h"
using namespace std;

//Data
//CONSTRUCTORS
template <typename T>
Data<T>::Data() { }

//DESTRUCTORS
template <typename T>
virtual Data<T>::~Data() { }

//AdjacencyList
//CONSTRUCTORS
template <typename T>
AdjacencyList<T>::AdjacencyList() { adj_list.clear(); }

template <typename T>
AdjacencyList<T>::AdjacencyList(Graph<T> &new_graph) { setGraph(new_graph); }

//DESTRUCTORS
template <typename T>
AdjacencyList<T>::~AdjacencyList() { adj_list.clear(); }

//ACCESSORS
template <typename T>
size_T AdjacencyList<T>::size() const { return adj_list.size(); }

template <typename T>
unsorted_set<unsigned> neighborhoodSizes() const {
    unsorted_set<unsigned> sizes;
    for_each(adj_list.cbegin(), adj_list.cend(), [](unordered_set<Vertex<T>&> &n) { sizes.push_back(n.size()); } );
    return sizes;
}

//MUTATORS
template <typename T>
void AdjacencyList<T>::setGraph(Graph<T> &new_graph) {
    adj_list.clear();
    for(Vertex<T> &v : new_graph.vertices) { adj_list.insert(new_graph.vertexNeighborhood(v));  }
}

//ITERATORS
template <typename T>
unordered_set<Vertex<T>&>::iterator& AdjacencyList<T>::begin() { return adj_list.begin(); }

template <typename T>
unordered_set<Vertex<T>&>::iterator& AdjacencyList<T>::end() { return adj_list.end(); }

template <typename T>
unordered_set<Vertex<T>&>::const_iterator AdjacencyList<T>::cbegin() const { return adj_list.cbegin(); }

template <typename T>
unordered_set<Vertex<T>&>::const_iterator AdjacencyList<T>::cend() const { return adj_list.cend(); }

//AdjacencyMatrix
//CONSTRUCTORS
template <typename T>
AdjacencyMatrix<T>::AdjacencyMatrix(): vertex_size(0) { adj_matrix.clear(); }

template <typename T>
AdjacencyMatrix<T>::AdjacencyMatrix(Graph<T> &new_graph) { setGraph(new_graph); }

//DESTRUCTORS
template <typename T>
AdjacencyMatrix<T>::~AdjacencyMatrix() { adj_matrix.clear(); vertex_size = 0; }

//ACCESSORS
template <typename T>
AdjacencyMatrix<T>::size_t size() const { return vertex_size(); }

//MUTATORS
template <typename T>
void setGraph(Graph<T> &new_graph) {
    adj_matrix.clear();
    vertex_size = new_graph.vertices.size();
    vector<bool> temp;
    for(auto it_row = new_graph.vertices.cbegin(); it_row != new_graph.vertices.cend(); it_row++) {
        temp.clear();
        for (auto it_col = new_graph.vertices.cbegin(); it_col != new_graph.vertices.cend(); it_col++) {
            temp.push_back(new_graph.containsEdge(*it_row, *it_col ));
        }
    }
}
