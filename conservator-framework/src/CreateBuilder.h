//
// Created by Ray Jenkins on 4/29/15.
//

#ifndef CONSERVATOR_CREATEBUILDER_H
#define CONSERVATOR_CREATEBUILDER_H

#include "PathableAndWriteable.h"

template<class T>
class CreateBuilder : public PathableAndWriteable<int> {
public:
    virtual ~CreateBuilder() {};
    virtual T forPath(string path) = 0;
    virtual T forPath(string path, char *data) = 0;
};


#endif //CONSERVATOR_CREATEBUILDER_H
