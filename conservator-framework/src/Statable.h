//
// Created by Ray Jenkins on 4/28/15.
//

#ifndef CONSERVATOR_STATABLE_H
#define CONSERVATOR_STATABLE_H

#include <iostream>
#include <zookeeper.jute.h>
#include "Pathable.h"
#include <memory>

using namespace std;

template<class T>
class Statable {

public:
    virtual Pathable<T>* storingStatIn(struct Stat* stat) = 0;
};

#endif //CONSERVATOR_STATABLE_H
