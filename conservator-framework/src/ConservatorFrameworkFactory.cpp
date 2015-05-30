//
// Created by Ray Jenkins on 4/25/15.
//

#include "ConservatorFrameworkFactory.h"

ConservatorFramework ConservatorFrameworkFactory::newClient(string connectString) {
    return ConservatorFramework(connectString);
}
ConservatorFramework ConservatorFrameworkFactory::newClient(string connectString, int timeout) {
    return ConservatorFramework(connectString, timeout);
}
ConservatorFramework ConservatorFrameworkFactory::newClient(string connectString, int timeout, clientid_t *cid) {
    return ConservatorFramework(connectString, timeout, cid);
}

ConservatorFramework ConservatorFrameworkFactory::newClient(string connectString, int timeout, clientid_t *cid,
                                                            int znode_size) {
    return ConservatorFramework(connectString, timeout, cid, znode_size);
}




