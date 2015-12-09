//
// Created by rjenkins on 5/30/15.
//

#ifndef CONSERVATOR_SETACLBUILDERIMPL_H
#define CONSERVATOR_SETACLBUILDERIMPL_H


#include <zookeeper.h>
#include "SetACLBuilder.h"

class SetACLBuilderImpl : public SetACLBuilder<int> {
public:
    virtual ~SetACLBuilderImpl() { }
    SetACLBuilderImpl(zhandle_t *zk, ACL_vector *vector);
    Pathable<int>* withVersion(int version);
    int forPath(string path);
private:
    zhandle_t *zk;
    ACL_vector *vector = NULL;
    int version = -1;

};


#endif //CONSERVATOR_SETACLBUILDERIMPL_H
