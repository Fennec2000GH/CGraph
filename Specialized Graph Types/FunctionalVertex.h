
#pragma once
#include "../Graph Structures/Vertex.h"
#include <cstdarg>
#include <functional>
#include <iostream>
using namespace std;

#ifndef CGRAPH_FUNCTIONALVERTEX_H
#define CGRAPH_FUNCTIONALVERTEX_H

template <typename T, typename S, typename ... P>
class FunctionalVertex : public Vertex<T> {
public:
    //CONSTRUCTORS
    FunctionalVertex();
    FunctionalVertex(function<T(P ...args)> new_func);
    FunctionalVertex(const FunctionalVertex<T, S, P...> &other_fv);

    //DESTRUCTORS
    ~FunctionalVertex();

    //ACCESSORS
    T apply(P ...);

    //MUTATORS
    void setFunction(function<T(S first , P ...args)> newFunc);

private:
    //MEMBER VARIABLES
    function<T(P ...args)> func;

};


#endif //CGRAPH_FUNCTIONALVERTEX_H
