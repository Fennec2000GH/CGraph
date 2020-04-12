
#include "Edge.h"
#include <optional>
using namespace std;

//CONSTRUCTORS
/* Constructor creates new undirected and unweighted edge from two (2) vertices */
template <typename T>
Edge<T>::Edge(const Vertex<T> &new_v1, const Vertex<T> &new_v2): v1(new_v1), v2(new_v2) {
    directed = false;
    weight = nullopt;
}

/* Constructor creates new unweighted edge from two (2) vertices and possibly applies directionality */
template <typename T>
Edge<T>::Edge(const Vertex<T> &new_v1, const Vertex<T> &new_v2, bool new_directed): Edge<T>(new_v1, new_v2) {
    directed = new_directed;
    weight = nullopt;
}

/* Constructor creates new from two (2) vertices and possibly applies directionality and/or weight */
template <typename T>
Edge<T>::Edge(const Vertex<T> &new_v1, const Vertex<T> &new_node2, bool new_directed, double new_weight): Edge<T>(new_v1, new_node2, new_directed) {
    weight = new_weight;
}
/* Copy constructor performs a deep copy of another edge */
template <typename T>
Edge<T>::Edge(const Edge<T> &other_edge): v1(new Vertex(other_edge.v1)), v2(new Vertex(other_edge.v2)), directed(other_edge.directed), weight(other_edge.weight.value()) {}

//DESTRUCTORS
/* Destructs edge supposedly, but no dynamic memory is used by the graph. */
template <typename T>
Edge<T>::~Edge() { }

//OPERATOR OVERLOADING
template <typename T>
bool Edge<T>::operator == (const Edge<T> &e) const {
    //base case: same exact reference
    if(&this == &e) { return true; }
    return (this -> v1 == e.v1) &&
           (this -> v2 == e.v2) &&
           (this -> directed == e.directed) &&
           !(this -> weight.has_value() ^ e.weight.has_value()) &&
           (this -> weight.value_or(-1) == e.weight.value_or(-1));
}

template <typename T>
bool Edge<T>::operator != (const Edge<T> &e) const {
    return (this -> v1 != e.v1) ||
           (this -> v2 != e.v2) ||
           (this -> directed != e.directed) ||
           (this -> weight.has_value() ^ e.weight.has_value()) ||
           (this -> weight.value_or(-1) != e.weight.value_or(-1));
}

template <typename T>
bool Edge<T>::operator <= (const Edge<T> &e) const {
    //definite false cases
    if(this -> weight.has_value() && !e.weight.has_value()) { return false; }
    return !(this -> weight.has_value()) || (this -> weight.value() <= e.weight.value());
}

template <typename T>
bool Edge<T>::operator >= (const Edge<T> &e) const {
    //definite false cases
    if(!(this -> weight.has_value()) && e.weight.has_value()) { return false; }
    return (!e.weight.has_value()) || (this -> weight.value() >= e.weight.value());
}

template <typename T>
bool Edge<T>::operator < (const Edge<T> &e) const {
    //definite false cases
    if(this -> weight.has_value() && !e.weight.has_value()) { return false; }
    if(!(this -> weight.has_value() || e.weight.has_value())) { return false; }
    return (!(this -> weight.has_value()) && e.weight.has_value()) || (this -> weight.value() < e.weight.value());
}

template <typename T>
bool Edge<T>::operator > (const Edge<T> &e) const {
    //definite false cases
    if(!(this -> weight.has_value()) && e.weight.has_value()) { return false; }
    if(!(this -> weight.has_value() || e.weight.has_value())) { return false; }
    return (this -> weight.has_value() && !e.weight.has_value()) || (this -> weight.value() > e.weight.value());
}

//ACCESSORS
/* Accesses the first endpoint */
template <typename T>
Vertex<T>& Edge<T>::first() const { return v1; }

/* Accesses the second endpoint */
template <typename T>
Vertex<T>& Edge<T>::second() const { return v2; }

/* Checks whether the edge has directionality */
template <typename T>
bool Edge<T>::isDirected() const { return directed; }

/* Checks whether the edge is weighted */
template <typename T>
bool Edge<T>::isWeighted() const { return weight.has_value(); }

/* Gets the weight of the edge, if exists */
template <typename T>
double Edge<T>::getWeight() const {
    if(!isWeighted()) { throw logic_error("Edge is not weighted!"); }
    return weight.value();
}

/* Checks whether edge is a self-loop */
template <typename T>
bool Edge<T>::isSelfLoop() const { return &v1 == &v2; }

//MUTATORS
/* Sets a new vertex to be the first endpoint. The old vertex loses the edge */
template <typename T>
void Edge<T>::setFirst(Vertex<T> &new_vertex1) { v1 = new_vertex1; }

/* Sets a new vertex to be the second endpoint. The old vertex loses the edge */
template <typename T>
void Edge<T>::setSecond(Vertex<T> &new_vertex2) { v2 = new_vertex2; }

/* Sets whether directionality exists or not for the edge */
template <typename T>
void Edge<T>::setDirected(bool new_directed) { directed = new_directed; }

/* Sets a new weight for the edge */
template <typename T>
void Edge<T>::setWeight(double new_weight) { weight = new_weight; }

int main() { return 0; }