
#include "Vertex.h"
using namespace std;

//Vertex
//CONSTRUCTORS
template <typename T>
Vertex<T>::Vertex(): id(-1), capacity(nullopt) { } //-1 indicates the absence of i.e. not enforced

template <typename T>
Vertex<T>::Vertex(T new_val): Vertex() { val = new_val; }

template <typename T>
Vertex<T>::Vertex(T new_val, unsigned new_capacity): Vertex(new_val) { capacity = new_capacity; }

template <typename T>
Vertex<T>::Vertex(const Vertex<T> &other_vertex): marker(other_vertex.marker), capacity(other_vertex.capacity.value()), val(other_vertex.val) {}

//DESTRUCTORS
template <typename T>
Vertex<T>::~Vertex() { }

//ACCESSORS
template <typename T>
int Vertex<T>::getID() const { return id; }

template <typename T>
bool Vertex<T>::isMarked() const { return marker; }

template <typename T>
bool Vertex<T>::hasCapacity() const { return capacity.has_value(); }

template <typename T>
unsigned Vertex<T>::getCapacity() const { return capacity.value_or(numeric_limits<unsigned>::infinity);  }

//MUTATORS
template <typename T>
void Vertex<T>::setMarked(bool new_marker) { marker = new_marker; }

int main() { return 0; }


