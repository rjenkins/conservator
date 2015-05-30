//
// Created by Ray Jenkins on 5/2/15.
//

#ifndef CONSERVATOR_DELETEBUILDER_H
#define CONSERVATOR_DELETEBUILDER_H

#include "Pathable.h"
#include "ChildrenDeletable.h"

template<class T>
class DeleteBuilder : public Pathable<int>, public ChildrenDeletable<int> {
public:
    virtual ~DeleteBuilder() {};
    virtual Pathable<T>* deletingChildren() = 0;
    virtual T forPath(string path) = 0;
};
#endif //CONSERVATOR_DELETEBUILDER_H
