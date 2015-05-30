//
// Created by rjenkins on 5/29/15.
//

#ifndef CONSERVATOR_VECTORPATHABLEANDWATCHABLE_H
#define CONSERVATOR_VECTORPATHABLEANDWATCHABLE_H

#include <iostream>
#include <zookeeper.h>
#include "vector"
#include "VectorPathable.h"
#include "Pathable.h"

using namespace std;
using std::vector;

template<class T>
class VectorPathableAndWatchable : public VectorPathable<T> {

public:
    virtual Pathable<vector<T>>* withWatcher(watcher_fn watcherFn, void* watcherCtx) = 0;
};
#endif //CONSERVATOR_VECTORPATHABLEANDWATCHABLE_H
