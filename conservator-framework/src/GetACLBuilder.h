//
// Created by rjenkins on 5/30/15.
//

#ifndef CONSERVATOR_GETACLBUILDER_H
#define CONSERVATOR_GETACLBUILDER_H

#include "Pathable.h"
#include "Statable.h"
#include "StatablePathable.h"

template<class T>
class GetACLBuilder : public StatablePathable<T>
{
public:
    virtual ~GetACLBuilder() {};
};

#endif //CONSERVATOR_GETACLBUILDER_H
