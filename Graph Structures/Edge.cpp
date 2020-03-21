
#include "Edge.h"
#include <optional>
using namespace std;

//CONSTRUCTORS
template <typename T>
Edge<T>::Edge(const Vertex<T> &new_v1, const Vertex<T> &new_v2): v1(new_v1), v2(new_v2) {
    directed = false;
    weight = nullopt;
}

template <typename T>
Edge<T>::Edge(const Vertex<T> &new_v1, const Vertex<T> &new_v2, bool new_directed): Edge<T>(new_v1, new_v2) {
    directed = new_directed;
    weight = nullopt;
}

template <typename T>
Edge<T>::Edge(const Vertex<T> &new_v1, const Vertex<T> &new_node2, bool new_directed, double new_weight): Edge<T>(new_v1, new_node2, new_directed) {
    weight = new_weight;
}

template <typename T>
Edge<T>::Edge(const Edge<T> &other_edge): v1(new Vertex(other_edge.v1)), v2(new Vertex(other_edge.v2)), directed(other_edge.directed), weight(other_edge.weight.value()) {}

//DESTRUCTORS
template <typename T>
Edge<T>::~Edge() { }

//ACCESSORS
template <typename T>
Vertex<T>& Edge<T>::first() const { return v1; }

template <typename T>
Vertex<T>& Edge<T>::second() const { return v2; }

template <typename T>
bool Edge<T>::isDirected() const { return directed; }

template <typename T>
bool Edge<T>::isWeighted() const { return weight.has_value(); }

template <typename T>
bool Edge<T>::getWeight() const { return weight.value_or(1); }

//MUTATORS
template <typename T>
void Edge<T>::setFirst(Vertex<T> &new_vertex1) { v1 = new_vertex1; }

template <typename T>
void Edge<T>::setSecond(Vertex<T> &new_vertex2) { v2 = new_vertex2; }

template <typename T>
void Edge<T>::setDirected(bool new_directed) { directed = new_directed; }

template <typename T>
void Edge<T>::setWeight(double new_weight) { weight = new_weight; }

int main() { return 0; }