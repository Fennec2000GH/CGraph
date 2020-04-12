
#include "Vertex.h"
using namespace std;

//Vertex
//CONSTRUCTORS
/* Constructor creates new valueless vertex with no capacity enforced */
template <typename T>
Vertex<T>::Vertex(): id(-1), capacity(nullopt) { } //-1 indicates the absence of i.e. not enforced

/* Constructor applies given value to new vertex with no capacity enforced */
template <typename T>
Vertex<T>::Vertex(T new_val): Vertex() { val = new_val; }

/* Constructor applies given value and capacity to new vertex */
template <typename T>
Vertex<T>::Vertex(T new_val, unsigned new_capacity): Vertex(new_val) { capacity = new_capacity; }

/* Copy constructor performs deep copy of another vertex */
template <typename T>
Vertex<T>::Vertex(const Vertex<T> &other_vertex): marker(other_vertex.marker), capacity(other_vertex.capacity.value()), val(other_vertex.val) {}

//DESTRUCTORS
/* Destructs vertex supposedly, but no dynamic memory is used by the graph. */
template <typename T>
Vertex<T>::~Vertex() { }

//OPERATOR OVERLOADING
template <typename T>
bool Vertex<T>::operator == (const Vertex<T> &v) const {
    return (this -> val == v.val) &&
    (this -> id == v.id) &&
    (this -> marker == v.marker) &&
    (this -> capacity == v.capacity);
}

template <typename T>
bool Vertex<T>::operator != (const Vertex<T> &v) const {
    return (this -> val != v.val) ||
           (this -> id != v.id) ||
           (this -> marker != v.marker) ||
           (this -> capacity != v.capacity);
}

template <typename T>
bool Vertex<T>::operator >= (const Vertex<T> &v) const { return this -> val >= v.val; }

template <typename T>
bool Vertex<T>::operator <= (const Vertex<T> &v) const { return this -> val <= v.val; }

template <typename T>
bool Vertex<T>::operator < (const Vertex<T> &v) const { return this -> val < v.val; }

template <typename T>
bool Vertex<T>::operator > (const Vertex<T> &v) const { return this -> val > v.val; }

//ACCESSORS
/* Gets the ID */
template <typename T>
int Vertex<T>::getID() const { return id; }

/* Checks whether the boolean marker is true */
template <typename T>
bool Vertex<T>::isMarked() const { return marker; }

/* Checks whether capacity is enforced */
template <typename T>
bool Vertex<T>::hasCapacity() const { return capacity.has_value(); }

/* Gets the capacity, if exists */
template <typename T>
int Vertex<T>::getCapacity() const {
    //edge case: capacity is not enforced
    try { if(!hasCapacity()) { throw logic_error("Capacity is not enforced!"); } }
    catch (const logic_error &error) { error.what(); }
    return capacity.value_or(-1);
}

//MUTATORS
/* Sets new value for boolean marker */
template <typename T>
void Vertex<T>::setMarked(bool new_marker) { marker = new_marker; }

/* Checks whether this vertex equals to another vertex by containing the same values for each field (except ID) */
template <typename T>
bool Vertex<T>::equals(const Vertex<T> &other_vertex) const {
    //base case: same exact vertex by reference
    if(this == other_vertex) { return true; }
    return (this -> val == other_vertex.val) &&
    (this -> marker == other_vertex.marker) &&
    (this -> capacity == other_vertex.capacity);
}

int main() { return 0; }


