
#include "Node.h"
using namespace std;

//Node
//ACCESSORS
template <typename T>
Node<T>::Node(): id(-1), capacity(-1) { } //-1 indicates the absence of i.e. not enforced

template <typename T>
Node<T>::Node(T new_val): Node() { val = new_val; }

template <typename T>
Node<T>::Node(T new_val, int new_capacity): Node(new_val) { capacity = new_capacity; }

//ACCESSORS
template <typename T>
int Node<T>::get_id() const { return id; }

//SimpleNode
//CONSTRUCTORS
template <typename T>
SimpleNode<T>::SimpleNode() {}

template <typename T>
SimpleNode<T>::SimpleNode(T new_val): Node<T>(new_val) { }

template <typename T>
SimpleNode<T>::SimpleNode(T new_val, int new_capacity): Node<T>(new_val, new_capacity) { }

//ACCESSORS
template <typename T>
unordered_set<SimpleNode<T>*>& SimpleNode<T>::neighborhood() const { return neighbors; }

template <typename T>
size_t SimpleNode<T>::degree() const { return neighbors.size(); }

//MUTATORS
template <typename T>
bool SimpleNode<T>::insert_neighbor(Node<T> &node) {
    //edge case: capacity already met
    if(this -> capacity != -1 && neighbors.size() == this -> capacity) { return false; }

    //edge case: already a neighbor
    if(neighbors.find(&node) != neighbors.end()) { return false; }

    neighbors.insert(&node);
    return true;
}

template <typename T>
bool SimpleNode<T>::erase_neighbor(Node<T> &node) {
        //edge case: empty or no neighbors
        if(neighbors.empty()) { return false; }

        //edge case: specified node not in neighborhood
        if(neighbors.find(&node) == neighbors.end()) { return false; }

        neighbors.erase(&node);
        return true;
}

//DirectedNode
//CONSTRUCTORS
template <typename T>
DirectedNode<T>::DirectedNode(): Node<T>() { }

template <typename T>
DirectedNode<T>::DirectedNode(T new_val): Node<T>(new_val) { }

template <typename T>
DirectedNode<T>::DirectedNode(T new_val, int new_capacity): Node<T>(new_val, new_capacity) { }

//ACCESSORS
template <typename T>
size_t DirectedNode<T>::degree() const { return in_degree() + out_degree(); }

template <typename T>
size_t DirectedNode<T>::in_degree() const { return in_neighbors.size(); }

template <typename T>
size_t DirectedNode<T>::out_degree() const { return out_neighbors.size(); }

//MUTATORS
//deprecated
template <typename T>
bool DirectedNode<T>::insert_neighbor(Node<T> &node) { return false; }

//deprecated
template <typename T>
bool erase_neighbor(Node<T> &node) { return false; }

template <typename T>
bool DirectedNode<T>::insert_out_neighbor(Node<T> &node) {
    //edge case: capacity already met
    if(this -> capacity != -1 && (int)degree() == this -> capacity) { return false; }

    //edge case: already a neighbor
    if(out_neighbors.find(&node) != out_neighbors.end()) { return false; }

    out_neighbors.insert(&node);
    return true;
}

template <typename T>
bool DirectedNode<T>::insert_in_neighbor(Node<T> &node) {
    //edge case: capacity already met
    if(this -> capacity != -1 && (int)degree() == this -> capacity) { return false; }

    //edge case: already a neighbor
    if(in_neighbors.find(&node) != in_neighbors.end()) { return false; }

    in_neighbors.insert(&node);
    return true;

}

template <typename T>
bool DirectedNode<T>::erase_in_neighbor(Node<T> &node) {
    //edge case: empty or no in-neighbors
    if(in_neighbors.empty()) { return false; }

    //edge case: specified node not in in-neighborhood
    if(in_neighbors.find(&node) == in_neighbors.end()) { return false; }

    in_neighbors.erase(&node);
    return true;
}

template <typename T>
bool DirectedNode<T>::erase_out_neighbor(Node<T> &node) {
    //edge case: empty or no out-neighbors
    if(out_neighbors.empty()) { return false; }

    //edge case: specified node not in out-neighborhood
    if(out_neighbors.find(&node) == out_neighbors.end()) { return false; }

    out_neighbors.erase(&node);
    return true;
}

int main() { return 0; }


