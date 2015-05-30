//
// Created by Ray Jenkins on 4/27/15.
//

#ifndef CONSERVATOR_GETDATABUILDER_H
#define CONSERVATOR_GETDATABUILDER_H


#include <zookeeper.jute.h>
#include "Pathable.h"
#include "Statable.h"
#include "Watchable.h"
#include <memory>

template<class T>
class GetDataBuilder : public Pathable<string>, public Statable<string>, public Watchable<string> {
public:
    virtual ~GetDataBuilder() {};
    virtual T forPath(string path) = 0;
    virtual Pathable<T>* withWatcher(watcher_fn watcherFn, void * watcherCtx) = 0;
    virtual Pathable<T>* storingStatIn(struct Stat* stat) = 0;
};

#endif //CONSERVATOR_GETDATABUILDER_H
