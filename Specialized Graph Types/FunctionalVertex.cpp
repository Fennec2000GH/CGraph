
#include "FunctionalVertex.h"
using namespace std;

//FunctionalVertex
//CONSTRUCTORS
template <typename T, typename S, typename ... P>
FunctionalVertex<T, S, P ... >::FunctionalVertex() { func = nullptr; }

template <typename T, typename S, typename ... P>
FunctionalVertex<T, S, P ...>::FunctionalVertex(function<T(P ...args)> new_func):func(new_func) { }

template <typename T, typename S, typename ... P>
FunctionalVertex<T, S, P ...>::FunctionalVertex(const FunctionalVertex<T, P ...> &other_fv) { func = other_fv.func; }

//DESTRUCTORS
template <typename T, typename S, typename ... P>
FunctionalVertex<T, S, P ...>::~FunctionalVertex() { }

//ACCESSORS
template <typename T, typename S, typename ... P>
T FunctionalVertex<T, S, P ...>::apply(S start, P ...args) { return bind(func, start, ...args); }

//MUTATORS
template <typename T, typename S, typename ... P>
void FunctionalVertex<T, S, P ...>::setFunction(function<T(P...)> newFunc) { func = newFunc; }

int main() { return 0; }
