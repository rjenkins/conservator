//
// Created by Ray Jenkins on 4/29/15.
//

#ifndef CONSERVATOR_CREATEBUILDERIMPL_H
#define CONSERVATOR_CREATEBUILDERIMPL_H


#include <zookeeper.h>
#include <iostream>
#include "CreateBuilder.h"

using namespace std;

class CreateBuilderImpl : public CreateBuilder<int> {
public:
    virtual ~CreateBuilderImpl() { cout << "~CreateBuilderImpl" << endl;}
    CreateBuilderImpl(zhandle_t *zk);
    int forPath(string path);
    int forPath(string path, char *data);
private:
    zhandle_t *zk;
};


#endif //CONSERVATOR_CREATEBUILDERIMPL_H
