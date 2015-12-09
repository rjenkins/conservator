//
// Created by Ray Jenkins on 4/28/15.
//

#ifndef CONSERVATOR_EXISTSBUILDERIMPL_H
#define CONSERVATOR_EXISTSBUILDERIMPL_H

#include <stdbool.h>
#include <zookeeper.h>
#include "ExistsBuilder.h"

class ExistsBuilderImpl : public ExistsBuilder<int> {
public:
    virtual ~ExistsBuilderImpl() { }
    ExistsBuilderImpl(zhandle_t *zk);
    Pathable<int>* withWatcher(watcher_fn watcherFn, void * watcherCtx);
    ZOOAPI int forPath(string path);
private:
    zhandle_t *zk;
    watcher_fn watcherFn = NULL;
    void * watcherCtx = NULL;
};


#endif //CONSERVATOR_EXISTSBUILDERIMPL_H
