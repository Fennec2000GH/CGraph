
#include <unordered_set>
#include <vector>
using namespace std;

#ifndef CGRAPH_NODE_H
#define CGRAPH_NODE_H

template <typename T = int>
class Node {
public:
    //CONSTRUCTORS
    Node();
    Node(T new_val);
    Node(T new_val, int new_capacity);

    //ACCESSORS
    int get_id() const;
    virtual size_t degree() const = 0;

protected:
    //MUTATORS
    virtual bool insert_neighbor(Node<T> &node) = 0;
    virtual bool erase_neighbor(Node<T> &node) = 0;

    //MEMBER VARIABLES
    int id;
    int capacity;
    T val;

};

template <typename T = int>
class SimpleNode : public Node<T> {
public:
    //CONSTRUCTORS
    SimpleNode();
    SimpleNode(T new_val);
    SimpleNode(T new_val, int new_capacity);

    //ACCESSORS
    unordered_set<SimpleNode<T>*>& neighborhood() const;
    size_t degree() const;

private:
    //MUTATORS
    bool insert_neighbor(Node<T> &node);
    bool erase_neighbor(Node<T> &node);

    //MEMBER VARIABLES
    unordered_set<SimpleNode<T>*> neighbors;

};

template <typename T = int>
class DirectedNode : public Node<T> {
public:
    //CONSTRUCTORS
    DirectedNode();
    DirectedNode(T new_val);
    DirectedNode(T new_val, int new_capacity);

    //ACCESSORS
    size_t degree() const;
    size_t in_degree() const;
    size_t out_degree() const;

private:
    //MUTATORS
    bool insert_neighbor(Node<T> &node);
    bool erase_neighbor(Node<T> &node);
    bool insert_in_neighbor(Node<T> &node);
    bool insert_out_neighbor(Node<T> &node);
    bool erase_in_neighbor(Node<T> &node);
    bool erase_out_neighbor(Node<T> &node);

    //MEMBER VARIABLES
    unordered_set<DirectedNode<T>*> in_neighbors;
    unordered_set<DirectedNode<T>*> out_neighbors;

};

#endif //CGRAPH_NODE_H
