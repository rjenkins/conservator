//
// Created by Ray Jenkins on 4/29/15.
//

#include <sstream>
#include "CreateBuilderImpl.h"

CreateBuilderImpl::CreateBuilderImpl(zhandle_t *zk) {
    this->zk = zk;
}

int CreateBuilderImpl::forPath(string path) {
    return this->forPath(path, NULL);
}

PathableAndWriteable<int> *CreateBuilderImpl::withFlags(int flags) {
    this->flags = flags;
    return (PathableAndWriteable<int> *) this;

}

int CreateBuilderImpl::forPath(string path, const char *data) {
    string result_path;
    return this->forPath(path, data, result_path);
}

int CreateBuilderImpl::forPath(string path, const char *data, string& result_path) {
    int length;
    if (data == NULL) {
        length = -1;
    } else {
        length = char_traits<const char>::length(data);
    }

    char buff[512] = {0};
    int ret = zoo_create(this->zk, path.c_str(), data, length, &ZOO_OPEN_ACL_UNSAFE, flags, buff, sizeof(buff)-1);

    result_path.assign(buff);
    return ret;
}

