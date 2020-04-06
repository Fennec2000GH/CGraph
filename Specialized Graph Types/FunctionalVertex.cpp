
#include "FunctionalVertex.h"
using namespace std;

//FunctionalVertex
//CONSTRUCTORS
template <typename T, typename... P>
FunctionalVertex<T, P...>::FunctionalVertex() { func = nullptr; }

template <typename T, typename... P>
FunctionalVertex<T, P...>::FunctionalVertex(function<T(P...)> new_func):func(new_func) { }

template <typename T, typename... P>
FunctionalVertex<T, P...>::FunctionalVertex(const FunctionalVertex<T, P...> &other_fv) { func = other_fv.func; }

//DESTRUCTORS
template <typename T, typename... P>
FunctionalVertex<T, P...>::~FunctionalVertex() { }

int main() { return 0; }
