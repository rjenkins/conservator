//
// Created by Ray Jenkins on 5/2/15.
//

#include <string.h>
#include "DeleteBuilderImpl.h"

DeleteBuilderImpl::DeleteBuilderImpl(zhandle_t *zk) {
    this->zk = zk;
}

Pathable<int>* DeleteBuilderImpl::deletingChildren() {
    this->deleteChildren = true;
    return this;
}

int DeleteBuilderImpl::forPath(string path) {
    if (deleteChildren) {
        struct String_vector strings;
        if(zoo_get_children(zk, path.c_str(), -1, &strings) == ZNONODE) {
            return ZNONODE;
        } else if  (strings.count == 0) {
            return zoo_delete(this->zk, path.c_str(), -1);
        } else {
            for (int i = 0; i < strings.count; i++) {
                char result[1024];   // array to hold the result.
                strcpy(result, path.c_str()); // copy string one into the result.
                strcat(result, "/"); // append string two to the result.
                strcat(result, strings.data[i]); // append string two to the result.
                forPath(result);
            }
            return forPath(path);
        }
    } else {
        return zoo_delete(this->zk, path.c_str(), -1);
    }
}