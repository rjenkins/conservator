//
// Created by rjenkins on 5/27/15.
//

#include "GetChildrenBuilderImpl.h"

GetChildrenBuilderImpl::GetChildrenBuilderImpl(zhandle_t *zk) {
    this->zk = zk;
}

vector<string> GetChildrenBuilderImpl::forPath(string path) {
    struct String_vector strings;
    if(watcherFn == NULL) {
        zoo_get_children(zk, path.c_str(), -1, &strings);
    } else {
        zoo_wget_children(zk, path.c_str(), watcherFn, watcherCtx, &strings);
    }
    vector<string> results = vector<string>();

    for(int i=0; i<strings.count; i++) {
        results.push_back(string(strings.data[i]));
    }

    return results;
}

Pathable<vector<string>> *GetChildrenBuilderImpl::withWatcher(watcher_fn watcherFn, void *watcherCtx) {
    this->watcherFn = watcherFn;
    this->watcherCtx = watcherCtx;
    return (Pathable<vector<string>>*) this;
}

