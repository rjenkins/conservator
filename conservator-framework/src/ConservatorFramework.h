//
// Created by Ray Jenkins on 4/20/15.
//

#ifndef CONSERVATOR_CONVERATORFRAMEWORK_H
#define CONSERVATOR_CONVERATORFRAMEWORK_H

#include <iostream>
#include <zookeeper.h>
#include <memory>
#include <vector>
#include "GetDataBuilder.h"
#include "GetDataBuilderImpl.h"
#include "ExistsBuilder.h"
#include "ExistsBuilderImpl.h"
#include "CreateBuilder.h"
#include "CreateBuilderImpl.h"
#include "DeleteBuilder.h"
#include "DeleteBuilderImpl.h"
#include "SetDataBuilder.h"
#include "GetChildrenBuilder.h"
#include "GetACLBuilder.h"
#include "SetACLBuilder.h"

using namespace std;

class ConservatorFramework {

public:
    ~ConservatorFramework() { cout << "~ConservatorFramework" << endl;}
    ConservatorFramework(string connectString);
    ConservatorFramework(string connectString, int timeout);
    ConservatorFramework(string connectString, int timeout, clientid_t *cid);
    ConservatorFramework(string connectString, int timeout, clientid_t *cid, int znode_size);
    void start();
    void close();
    ZOOAPI int getState();

    bool isStarted();

    unique_ptr<GetDataBuilder<string>> getData();
    unique_ptr<ExistsBuilder<int>> checkExists();
    unique_ptr<CreateBuilder<int>> create();
    unique_ptr<DeleteBuilder<int>> deleteNode();
    unique_ptr<SetDataBuilder<int>> setData();
    unique_ptr<GetChildrenBuilder<string>> getChildren();
    unique_ptr<GetACLBuilder<int>> getACL(ACL_vector *vector);
    unique_ptr<SetACLBuilder<int>> setACL(ACL_vector *vector);

    string get(string path);
    string get(string path, int length);
private:
    zhandle_t *zk;
    string connectString;
    bool started = false;
    int timeout = 100000;
    clientid_t *cid = 0;
    int znode_size = 1024 * 1024; // default znode is 1MB
};

#endif //CONSERVATOR_CONVERATORFRAMEWORK_H
