//
// Created by Ray Jenkins on 4/28/15.
//

#ifndef CONSERVATOR_EXISTSBUILDER_H
#define CONSERVATOR_EXISTSBUILDER_H


#include "Pathable.h"
#include "Watchable.h"
#include "zookeeper.h"
#include "PathableAndWatchable.h"

template<class T>
class ExistsBuilder : public PathableAndWatchable<int> {
public:
    virtual ~ExistsBuilder() {};
    virtual Pathable<T>* withWatcher(watcher_fn watcher, void * watcherCtx) = 0;
    virtual T forPath(string path) = 0;
};


#endif //CONSERVATOR_EXISTSBUILDER_H
