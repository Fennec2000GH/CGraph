
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

template <typename T>
size_t Vertex<T>::degree() const { return neighbors.size(); }

template <typename T>
unordered_set<Vertex<T>&> Vertex<T>::vertexNeighborhood() const {
    unordered_set<Vertex<T>&> adj_vertices;
    for(Edge<T> &e : neighbors) { adj_vertices.insert(e.first() != this ? e.first() : e.second()); }
    return adj_vertices;
}

template <typename T>
unordered_set<Edge<T>&> Vertex<T>::edgeNeighborhood() const { return neighbors; }

//MUTATORS
template <typename T>
void Vertex<T>::setMarked(bool new_marker) { marker = new_marker; }

template <typename T>
void Vertex<T>::increaseCapacity(unsigned new_capacity) {
    //edge case: new_capacity is less than current capacity
    if(new_capacity < getCapacity()) { throw invalid_argument("New capacity must be higher than or equal to current capacity!"); }

    capacity = new_capacity;
}

template <typename T>
void Vertex<T>::decreaseCapacity(unsigned new_capacity, unordered_set<Edge<T>&> to_delete) {
    //edge case: new_capacity is more than or equal to current capacity
    if(new_capacity >= getCapacity()) { throw invalid_argument("New capacity must be less than current capacity!"); }

    //edge case: some or all edges to be deleted are not actual edges of vertex
    for(Edge<T> &e : to_delete) {
        if(neighbors.find(e) == neighbors.end()) {
            throw invalid_argument("Some or all edges to be deleted are not even present in neighborhood!");
        }
    }

    for(Edge<T> &e : to_delete) { neighbors.erase(e); }
}

template <typename T>
void Vertex<T>::decreaseCapacity(unsigned new_capacity, unordered_set<Vertex<T>&> to_delete) {
    //edge case: new_capacity is more than or equal to current capacity
    if(new_capacity >= getCapacity()) { throw invalid_argument("New capacity must be less than current capacity!"); }

    //edge case: some or all edges to be deleted are not actual edges of vertex
    unordered_set<Vertex<T>&> adj_vertices = vertexNeighborhood();
    for(Vertex<T> &v : to_delete) {
        if(adj_vertices.find(v) == adj_vertices.end()) {
            throw invalid_argument("Some or all edges to be deleted are not even present in neighborhood!");
        }
    }
}

int main() { return 0; }


