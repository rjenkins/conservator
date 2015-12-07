//
// Created by Ray Jenkins on 4/25/15.
//

#include "ConservatorFrameworkFactory.h"

unique_ptr<ConservatorFramework> ConservatorFrameworkFactory::newClient(string connectString) {
    return unique_ptr<ConservatorFramework>(new ConservatorFramework(connectString));
}
unique_ptr<ConservatorFramework> ConservatorFrameworkFactory::newClient(string connectString, int timeout) {
    return unique_ptr<ConservatorFramework>(new ConservatorFramework(connectString, timeout));
}
unique_ptr<ConservatorFramework> ConservatorFrameworkFactory::newClient(string connectString, int timeout, clientid_t *cid) {
    return unique_ptr<ConservatorFramework>(new ConservatorFramework(connectString, timeout, cid));
}

unique_ptr<ConservatorFramework> ConservatorFrameworkFactory::newClient(string connectString, int timeout, clientid_t *cid,
                                                            int znode_size) {
    return unique_ptr<ConservatorFramework>(new ConservatorFramework(connectString, timeout, cid, znode_size));
}




