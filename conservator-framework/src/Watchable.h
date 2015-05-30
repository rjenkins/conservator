//
// Created by Ray Jenkins on 4/27/15.
//

#ifndef CONSERVATOR_WATCHABLE_H
#define CONSERVATOR_WATCHABLE_H

#include <iostream>
#include "Pathable.h"

using namespace std;

template<class T>
class Watchable {
public:
    virtual Pathable<T>* withWatcher(watcher_fn watcherFn, void * watcherCtx) = 0;
};


#endif //CONSERVATOR_WATCHABLE_H
