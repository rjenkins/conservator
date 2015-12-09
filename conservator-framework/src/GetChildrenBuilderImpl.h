//
// Created by rjenkins on 5/27/15.
//

#ifndef CONSERVATOR_GETCHILDRENBUILDERIMPL_H
#define CONSERVATOR_GETCHILDRENBUILDERIMPL_H


#include <iostream>
#include <zookeeper.h>
#include "GetChildrenBuilder.h"
#include "vector"
#include "string"
#include "Pathable.h"

using namespace std;
using std::vector;

class GetChildrenBuilderImpl : public GetChildrenBuilder<string> {
public:
    virtual ~GetChildrenBuilderImpl() { }
    GetChildrenBuilderImpl(zhandle_t *zk);
    Pathable<vector<string>> *withWatcher(watcher_fn watcherFn, void *watcherCtx);
    vector<string> forPath(string path);

private:
    zhandle_t *zk = NULL;
    watcher_fn watcherFn = NULL;
    void * watcherCtx = NULL;
};


#endif //CONSERVATOR_GETCHILDRENBUILDERIMPL_H
