//
// Created by rjenkins on 5/26/15.
//

#include "SetDataBuilderImpl.h"

SetDataBuilderImpl::SetDataBuilderImpl(zhandle_t *zk) {
    this->zk = zk;
}

ZOOAPI int SetDataBuilderImpl::forPath(string path) {
    char buffer[0];
    return zoo_set(zk, path.c_str(), buffer, 0, version);
}

ZOOAPI int SetDataBuilderImpl::forPath(string path, const char *data) {
   int length;
    if(data == NULL) {
        length = -1;
    } else {
        length = char_traits<const char>::length(data);
    }
    return zoo_set(zk, path.c_str(), data, length, version);
}

ZOOAPI int SetDataBuilderImpl::forPath(string path, const char *data, string&) {
    return this->forPath(path, data);
}

PathableAndWriteable<int>* SetDataBuilderImpl::withVersion(int version) {
    this->version = version;
    return (PathableAndWriteable<int> *) this;
}

