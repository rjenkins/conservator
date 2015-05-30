//
// Created by rjenkins on 5/30/15.
//

#ifndef CONSERVATOR_SETACLBUILDER_H
#define CONSERVATOR_SETACLBUILDER_H

#include "ACLVersionable.h"

template<class T>
class SetACLBuilder : public ACLVersionable<T>
{
public:
    virtual ~SetACLBuilder() {};
};

#endif //CONSERVATOR_SETACLBUILDER_H
