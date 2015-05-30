//
// Created by Ray Jenkins on 4/27/15.
//

#include <zookeeper.h>
#include "GetDataBuilderImpl.h"

GetDataBuilderImpl::GetDataBuilderImpl(zhandle_t *zk, int znode_size) {
    this->zk = zk;
    this->znode_size = znode_size;
}

string GetDataBuilderImpl::forPath(string path) {
    return forPath(path, znode_size);
}

Pathable<string>* GetDataBuilderImpl::withWatcher(watcher_fn watcherFn, void *watcherCtx) {
    this->watcherFn = watcherFn;
    this->watcherCtx = watcherCtx;
    return (Pathable<string> *) this;
}

Pathable<string>* GetDataBuilderImpl::storingStatIn(struct Stat *stat) {
    this->stat = stat;
    return (Pathable<string> *) this;
}

string GetDataBuilderImpl::forPath(string path, int length) {
    struct Stat *s = NULL;
    if (this->stat != NULL) {
        s = this->stat;
    }
    char buff[length];
    if (watcherFn == NULL) {
        zoo_get(zk, path.c_str(), 0, buff, &length, s);
    } else {
        zoo_wget(zk, path.c_str(), watcherFn, watcherCtx, buff, &length, s);
    }


    if (length == -1) {
        return string();
    } else {
        return string(buff);
    }
}