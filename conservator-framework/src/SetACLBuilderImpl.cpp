//
// Created by rjenkins on 5/30/15.
//

#include "SetACLBuilderImpl.h"

SetACLBuilderImpl::SetACLBuilderImpl(zhandle_t *zk, ACL_vector *vector) {
    this->zk = zk;
    this->vector = vector;
}

Pathable<int>* SetACLBuilderImpl::withVersion(int version) {
    this->version = version;
    return (Pathable<int> *) this;
}

int SetACLBuilderImpl::forPath(string path) {
    return zoo_set_acl(zk, path.c_str(), version, vector);
}
