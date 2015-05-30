//
// Created by rjenkins on 5/27/15.
//

#ifndef CONSERVATOR_GETCHILDRENBUILDER_H
#define CONSERVATOR_GETCHILDRENBUILDER_H

#include "vector"
#include "VectorPathableAndWatchable.h"

using namespace std;
using std::vector;

template<class T>
class GetChildrenBuilder : public VectorPathableAndWatchable<T> {
public:
    virtual ~GetChildrenBuilder() {};
    virtual vector<T> forPath(string path) = 0;
    virtual Pathable<vector<T>> *withWatcher(watcher_fn watcherFn, void *watcherCtx) = 0;
};

#endif //CONSERVATOR_GETCHILDRENBUILDER_H
