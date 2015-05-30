//
// Created by rjenkins on 5/30/15.
//

#ifndef CONSERVATOR_ACLVERSIONABLE_H
#define CONSERVATOR_ACLVERSIONABLE_H

#include "Pathable.h"

template<class T>
class ACLVersionable : public Pathable<T> {
public:
    virtual Pathable<T>* withVersion(int version) = 0;
};
#endif //CONSERVATOR_ACLVERSIONABLE_H
