//
// Created by rjenkins on 5/30/15.
//

#include "GetACLBuilderImpl.h"

GetACLBuilderImpl::GetACLBuilderImpl(zhandle_t *zk, ACL_vector *vector) {
    this->zk = zk;
    this->vector = vector;
}

Pathable<int>* GetACLBuilderImpl::storingStatIn(struct Stat *stat) {
    this->stat = stat;
    return (Pathable<int> *) this;
}

int GetACLBuilderImpl::forPath(string path) {
    struct Stat *s = NULL;
    if (this->stat != NULL) {
        s = this->stat;
    }

    return zoo_get_acl(zk, path.c_str(), vector, s);
}


