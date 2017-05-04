//
// Created by Ray Jenkins on 4/29/15.
//

#ifndef CONSERVATOR_CREATEBUILDER_H
#define CONSERVATOR_CREATEBUILDER_H

#include "PathableAndWriteable.h"
#include "Flagable.h"

template<class T>
class CreateBuilder : public Flagable<T>, public PathableAndWriteable<T> {
public:
    virtual ~CreateBuilder() {};
    virtual PathableAndWriteable<T> *withFlags(int flags) = 0;
    virtual T forPath(string path) = 0;
    virtual T forPath(string path, const char *data) = 0;
    virtual T forPath(string path, const char *data, string& result_path) = 0;
};
#endif //CONSERVATOR_CREATEBUILDER_H

