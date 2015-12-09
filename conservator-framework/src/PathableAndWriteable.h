//
// Created by Ray Jenkins on 4/29/15.
//

#ifndef CONSERVATOR_PATHABLEANDWRITEABLE_H
#define CONSERVATOR_PATHABLEANDWRITEABLE_H

#include <iostream>
using namespace std;

template<class T>
class PathableAndWriteable {

public:
    virtual T forPath(string path) = 0;
    virtual T forPath(string path, const char *data) = 0;
};


#endif //CONSERVATOR_PATHABLEANDWRITEABLE_H
