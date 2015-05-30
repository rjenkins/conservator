//
// Created by rjenkins on 5/28/15.
//

#ifndef CONSERVATOR_CHILDRENDELETABLE_H
#define CONSERVATOR_CHILDRENDELETABLE_H

#include "Pathable.h"

template<class T>
class ChildrenDeletable {
public:
    virtual Pathable<T>* deletingChildren() = 0;
};
#endif //CONSERVATOR_CHILDRENDELETABLE_H
