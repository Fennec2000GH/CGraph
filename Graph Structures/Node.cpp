
#include "Node.h"
using namespace std;

//Node
//CONSTRUCTORS
template <typename T>
Node<T>::Node(): id(-1), capacity(-1), self_loop(false) { } //-1 indicates the absence of i.e. not enforced

template <typename T>
Node<T>::Node(T new_val): Node() { val = new_val; }

template <typename T>
Node<T>::Node(T new_val, int new_capacity): Node(new_val) { capacity = new_capacity; }

//ACCESSORS
template <typename T>
int Node<T>::getId() const { return id; }

template <typename T>
bool Node<T>::isMarked() const { return marker; }

//MUTATORS
template <typename T>
void Node<T>::addEdge(Edge<T> &new_edge) { neighbors.insert(new_edge); }

template <typename T>
void Node<T>::setSelfloop(bool new_self_loop) { self_loop = new_self_loop; }

template <typename T>
void Node<T>::setMarked(bool new_marker) { marker = new_marker; }

template <typename T>
void Node<T>::increaseCapacity(unsigned new_capacity) {
    //edge case: new_capacity is less than current capacity
    if(new_capacity < getCapacity()) { throw invalid_argument("New capacity must be higher than or equal to current capacity!"); }

    capacity = new_capacity;
}

template <typename T>
void Node<T>::decreaseCapacity(unsigned new_capacity, unordered_set<Edge<T>&> to_delete) {
    //edge case: new_capacity is more than or equal to current capacity
    if(new_capacity >= getCapacity()) { throw invalid_argument("New capacity must be less than current capacity!"); }

    if(!all_of(to_delete.cbegin(), to_delete.cend(), [this](Edge<T> &edge){ return neighbors.find(edge) != neighbors.end(); })) {
        throw invalid_argument("Some or all edges to be deleted are not even present in neighborhood!");
    }

    for(Edge<T> &e : to_delete) { neighbors.erase(e); }
}

//template <typename T>
//void Node<T>::decreaseCapacity(unsigned new_capacity, unordered_set<Node<T>&> to_delete);

int main() { return 0; }


