//
// Created by rjenkins on 5/30/15.
//

#ifndef CONSERVATOR_FLAGABLE_H
#define CONSERVATOR_FLAGABLE_H

#include "PathableAndWriteable.h"

using namespace std;

template<class T>
class Flagable {

public:
    virtual PathableAndWriteable<T>* withFlags(int flags) = 0;
};
#endif //CONSERVATOR_FLAGABLE_H
