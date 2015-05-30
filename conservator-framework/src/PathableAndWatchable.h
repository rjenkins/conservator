//
// Created by rjenkins on 5/29/15.
//

#ifndef CONSERVATOR_PATHABLEANDWATCHABLE_H
#define CONSERVATOR_PATHABLEANDWATCHABLE_H

#include <iostream>
#include <zookeeper.h>
#include "Pathable.h"

using namespace std;

template<class T>
class PathableAndWatchable : public Pathable<T> {

public:
    virtual Pathable<T>* withWatcher(watcher_fn watcherFn, void* watcherCtx) = 0;
};



#endif //CONSERVATOR_PATHABLEANDWATCHABLE_H
