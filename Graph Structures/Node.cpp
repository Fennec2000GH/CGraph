
#include "Node.h"
using namespace std;

//Node
//ACCESSORS
template <typename T>
Node<T>::Node(): id(-1), capacity(-1), self_loop(false) { } //-1 indicates the absence of i.e. not enforced

template <typename T>
Node<T>::Node(T new_val): Node() { val = new_val; }

template <typename T>
Node<T>::Node(T new_val, int new_capacity): Node(new_val) { capacity = new_capacity; }

//ACCESSORS
template <typename T>
int Node<T>::get_id() const { return id; }

template <typename T>
bool Node<T>::marked() const { return marker; }

//MUTATORS
template <typename T>
void Node<T>::set_marker(bool new_marker) { marker = new_marker; }

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
size_t SimpleNode<T>::degree() const { return neighbors.size() + (this -> self_loop ? 1 : 0); }

//MUTATORS
template <typename T>
bool SimpleNode<T>::insert_neighbor(Node<T> &node) {
    //edge case: capacity already met
    if(this -> capacity != -1 && neighbors.size() == this -> capacity) { return false; }

    //edge case: already a neighbor
    if(neighbors.find(&node) != neighbors.end()) { return false; }

    //edge case: attempt to make self-loop
    if(this == node) { return false; }

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

template <typename T>
void SimpleNode<T>::set_self_loop(bool loop) {
    //edge case: self-loop condition does not change
    if(this -> has_self_loop() == loop) { return; }

    this -> self_loop = loop;
    if(loop) { insert_neighbor(this); }
    else { erase_neighbor(this); }
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
bool DirectedNode<T>::insert_in_neighbor(Node<T> &node) {
    //edge case: capacity already met
    if(this -> capacity != -1 && (int)degree() == this -> capacity) { return false; }

    //edgw case: already a neighbor
    if(in_neighbors.find(&node) != in_neighbors.end()) { return false; }

    in_neighbors.insert(&node);
    return true;
}

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

template <typename T>
void DirectedNode<T>::set_self_loop(bool loop) {
    //edge case: self-loop condition does not change
    if(Node<T>::has_self_loop() == loop) { return; }

    Node<T>::self_loop = loop;
    if(loop) {
        insert_in_neighbor(this);
        insert_out_neighbor(this);
    } else {
        erase_in_neighbor(this);
        erase_out_neighbor(this);
    }
}

int main() { return 0; }


