
#pragma once
#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;

int main() {
    volatile int x = 6;
    cout << x << endl;
    const volatile int * y_ptr = &as_const(x);
//    *y_ptr = 8;
    cout << *y_ptr << endl;
    add_const<int>::type z = 12;
    cout << z << endl;
//    z = 24;
//    cout << z << endl;

    return 0;
}

