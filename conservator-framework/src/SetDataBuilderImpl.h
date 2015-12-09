
// Created by rjenkins on 5/26/15.


#ifndef CONSERVATOR_SETDATABUILDERIMPL_H
#define CONSERVATOR_SETDATABUILDERIMPL_H

#include <zookeeper.h>
#include "SetDataBuilder.h"
#include <iostream>

using namespace std;

class SetDataBuilderImpl : public SetDataBuilder<int> {

public:
    virtual ~SetDataBuilderImpl() { }
    SetDataBuilderImpl(zhandle_t *zk);
    ZOOAPI int forPath(string path);
    ZOOAPI int forPath(string path, char *data);
    PathableAndWriteable<int>* withVersion(int version);
private:
    zhandle_t *zk = NULL;
    int version = -1;
};


#endif //CONSERVATOR_SETDATABUILDERIMPL_H
