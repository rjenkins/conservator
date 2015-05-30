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
        printf("Getting children with watch\n");
        zoo_wget_children(zk, path.c_str(), watcherFn, watcherCtx, &strings);
        printf("Getting children with watch complete\n");
    }
    vector<string> results = vector<string>();
    printf("strings is %p\n", &strings);
    printf("strings.count is %d\n", strings.count);
    for(int i=0; i<strings.count; i++) {
        results.push_back(string(strings.data[i]));
    }

    printf("returning results of %p\n", &results);
    return results;
}

Pathable<vector<string>> *GetChildrenBuilderImpl::withWatcher(watcher_fn watcherFn, void *watcherCtx) {
    this->watcherFn = watcherFn;
    this->watcherCtx = watcherCtx;
    return (Pathable<vector<string>>*) this;
}

