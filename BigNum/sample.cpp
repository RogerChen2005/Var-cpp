#include "lintchar.hpp"
#include <cstdio>
#include <iostream>

using namespace std;

int main(){
    L_INT a,b;
    a = 1;b = 2;
    a.debug('a');b.debug('b');
    cout << a + b << endl;
    cout << "a:"<< a << endl;
    cout << "b:"<< b << endl;
    return 0;
}