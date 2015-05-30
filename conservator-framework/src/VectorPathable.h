//
// Created by rjenkins on 5/29/15.
//

#ifndef CONSERVATOR_VECTORPATHABLE_H
#define CONSERVATOR_VECTORPATHABLE_H
#include <iostream>
#include "vector"

using namespace std;

template<class T>
class VectorPathable {

public:
    virtual vector<T> forPath(string path) = 0;
};

#endif //CONSERVATOR_VECTORPATHABLE_H
