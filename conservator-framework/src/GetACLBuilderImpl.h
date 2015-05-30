//
// Created by rjenkins on 5/30/15.
//

#include <zookeeper.h>
#include "GetACLBuilder.h"

#ifndef CONSERVATOR_GETACLBUILDERIMPL_H
#define CONSERVATOR_GETACLBUILDERIMPL_H

class GetACLBuilderImpl : public GetACLBuilder<int> {

public:
    virtual ~GetACLBuilderImpl() { cout << "~GetACLBuilderImpl" << endl; }
    GetACLBuilderImpl(zhandle_t *zk, ACL_vector *vector);
    Pathable<int> *storingStatIn(struct Stat *stat);
    int forPath(string path);
private:
    zhandle_t *zk;
    Stat *stat = NULL;
    ACL_vector *vector = NULL;
};
#endif //CONSERVATOR_GETACLBUILDERIMPL_H

