//
// Created by Ray Jenkins on 4/25/15.
//

#ifndef CONSERVATOR_CONSERVATORFRAMEWORKFACTORY_H
#define CONSERVATOR_CONSERVATORFRAMEWORKFACTORY_H


#include "ConservatorFramework.h"
#include "zookeeper.h"

class ConservatorFrameworkFactory {

public:
    ConservatorFramework newClient(string connectString);
    ConservatorFramework newClient(string connectString, int timeout);
    ConservatorFramework newClient(string connectionString, int timeout, clientid_t *cid);
    ConservatorFramework newClient(string connectString, int timeout, clientid_t * cid, int znode_size);
};


#endif //CONSERVATOR_CONSERVATORFRAMEWORKFACTORY_H
