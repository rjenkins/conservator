//
// Created by rjenkins on 5/27/15.
//

#ifndef CONSERVATOR_VERSIONABLE_H
#define CONSERVATOR_VERSIONABLE_H

#include "PathableAndWriteable.h"

template<class T>
class Versionable {
public:
    virtual PathableAndWriteable<T>* withVersion(int version) = 0;
};
#endif //CONSERVATOR_VERSIONABLE_H
