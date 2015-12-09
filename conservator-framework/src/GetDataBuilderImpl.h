//
// Created by Ray Jenkins on 4/27/15.
//

#ifndef CONSERVATOR_GETDATABUILDERIMPL_H
#define CONSERVATOR_GETDATABUILDERIMPL_H

#include <zookeeper.h>
#include "GetDataBuilder.h"
#include <iostream>

using namespace std;

class GetDataBuilderImpl : public GetDataBuilder<string> {

public:
    virtual ~GetDataBuilderImpl() { }
    GetDataBuilderImpl(zhandle_t *zk, int znode_size);
    Pathable<string>* withWatcher(watcher_fn watcherFn, void * watcherCtx);
    Pathable<string>* storingStatIn(struct Stat* stat);
    string forPath(string path);
    string forPath(string path, int length);
private:
    zhandle_t *zk = NULL;
    struct Stat* stat = NULL;
    watcher_fn watcherFn = NULL;
    void * watcherCtx = NULL;
    int znode_size;
};


#endif //CONSERVATOR_GETDATABUILDERIMPL_H
