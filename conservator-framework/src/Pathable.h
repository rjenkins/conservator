//
// Created by Ray Jenkins on 4/27/15.
//

#ifndef CONSERVATOR_PATHABLE_H
#define CONSERVATOR_PATHABLE_H

#include <iostream>
using namespace std;

template<class T>
class Pathable {

public:
    virtual T forPath(string path) = 0;
};


#endif //CONSERVATOR_PATHABLE_H
