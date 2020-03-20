
#include "Edge.h"
#include <optional>
using namespace std;

//CONSTRUCTORS
template <typename T>
Edge<T>::Edge(Node<T> &new_node1, Node<T> &new_node2): node1(new_node1), node2(new_node2) {
    directed = false;
    weight = nullopt;
}

template <typename T>
Edge<T>::Edge(Node<T> &new_node1, Node<T> &new_node2, bool new_directed): Edge<T>(new_node1, new_node2) {
    directed = new_directed;
    weight = nullopt;
}

template <typename T>
Edge<T>::Edge(Node<T> &new_node1, Node<T> &new_node2, bool new_directed, double new_weight): Edge<T>(new_node1, new_node2, new_directed) {
    weight = new_weight;
}

//ACCESSORS
template <typename T>
Node<T>& Edge<T>::first() const { return node1; }

template <typename T>
Node<T>& Edge<T>::second() const { return node2; }

template <typename T>
bool Edge<T>::isDirected() const { return directed; }

template <typename T>
bool Edge<T>::isWeighted() const { return weight.has_value(); }

template <typename T>
bool Edge<T>::getWeight() const { return weight.value_or(1); }

//MUTATORS
template <typename T>
void Edge<T>::setFirst(Node<T> &new_node1) { node1 = new_node1; }

template <typename T>
void Edge<T>::setSecond(Node<T> &new_node2) { node2 = new_node2; }

template <typename T>
void Edge<T>::setDirected(bool new_directed) { directed = new_directed; }

template <typename T>
void Edge<T>::setWeight(double new_weight) { weight = new_weight; }

int main() { return 0; }