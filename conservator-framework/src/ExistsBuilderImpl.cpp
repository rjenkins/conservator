//
// Created by Ray Jenkins on 4/28/15.
//

#include "ExistsBuilderImpl.h"

ExistsBuilderImpl::ExistsBuilderImpl(zhandle_t *zk) {
    this->zk = zk;
}

Pathable<int>* ExistsBuilderImpl::withWatcher(watcher_fn watcherFn, void *watcherCtx) {
    this->watcherFn = watcherFn;
    this->watcherCtx = watcherCtx;
    return (Pathable<int>*) this;
}
int ExistsBuilderImpl::forPath(string path) {
    struct Stat stat;
    if(this->watcherFn == NULL) {
        printf("watcherFn is null calling zoo_exists on %s\n", path.c_str());
        return zoo_exists(zk, path.c_str(), 0, &stat);
    }

    return zoo_wexists(zk, path.c_str(), watcherFn, watcherCtx, &stat);
}
