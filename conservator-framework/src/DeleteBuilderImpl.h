//
// Created by Ray Jenkins on 5/2/15.
//

#ifndef CONSERVATOR_DELETEBUILDERIMPL_H
#define CONSERVATOR_DELETEBUILDERIMPL_H

#include <zookeeper.h>
#include <iostream>
#include "DeleteBuilder.h"

using namespace std;

class DeleteBuilderImpl : public DeleteBuilder<int> {
public:
    virtual ~DeleteBuilderImpl() { cout << "~DeleteBuilderImpl" << endl; }
    DeleteBuilderImpl(zhandle_t *zk);
    Pathable<int>* deletingChildren();
    int forPath(string path);
private:
    bool deleteChildren = false;
    zhandle_t *zk;
};


#endif //CONSERVATOR_DELETEBUILDERIMPL_H
