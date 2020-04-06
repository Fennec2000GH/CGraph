
#pragma once
#include "../Graph Structures/Vertex.h"
#include <functional>
using namespace std;

#ifndef CGRAPH_FUNCTIONALVERTEX_H
#define CGRAPH_FUNCTIONALVERTEX_H

template <typename T, typename... P>
class FunctionalVertex : public Vertex<T> {
public:
    //CONSTRUCTORS
    FunctionalVertex();
    FunctionalVertex(function<T(P...)> new_func);
    FunctionalVertex(const FunctionalVertex<T, P...> &other_fv);

    //DESTRUCTORS
    ~FunctionalVertex();

private:
    //MEMBER VARIABLES
    function<T(P...)> func;

};


#endif //CGRAPH_FUNCTIONALVERTEX_H
