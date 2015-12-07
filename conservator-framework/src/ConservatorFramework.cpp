//
// Created by Ray Jenkins on 4/20/15.
//

#include "ConservatorFramework.h"
#include "SetDataBuilderImpl.h"
#include "GetChildrenBuilderImpl.h"
#include "GetACLBuilderImpl.h"
#include "SetACLBuilderImpl.h"

void watcher(zhandle_t *zzh, int type, int state, const char *path,
             void *watcherCtx) {

    ConservatorFramework* framework = (ConservatorFramework *) watcherCtx;
    if(state == ZOO_CONNECTED_STATE) {
        unique_lock<std::mutex> connectLock(framework->connectMutex);
        framework->connected = true;
        framework->connectCondition.notify_all();
        connectLock.unlock();
    }
};

ConservatorFramework::ConservatorFramework(string connectString) {
    this->connectString = connectString;
}

ConservatorFramework::ConservatorFramework(string connectString, int timeout) {
    this->connectString = connectString;
    this->timeout = timeout;
}

ConservatorFramework::ConservatorFramework(string connectString, int timeout, clientid_t *cid) {
    this->connectString = connectString;
    this->timeout = timeout;
    this->cid = cid;
}

ConservatorFramework::ConservatorFramework(string connectString, int timeout, clientid_t *cid, int znode_size) {
    this->connectString = connectString;
    this->timeout = timeout;
    this->cid = cid;
    this->znode_size = znode_size;
}

void ConservatorFramework::start() {
    this->zk = zookeeper_init(connectString.c_str(), watcher, timeout, cid, (void *) this, 0);

    while(!connected) {
        unique_lock<std::mutex> connectLock(connectMutex);
        if(connectCondition.wait_for(connectLock, chrono::seconds(15)) == cv_status::timeout) {
            throw "timed out waiting to connect to zookeeper";
        }
        connectLock.unlock();
    }
    started = true;
}

void ConservatorFramework::close() {
    zookeeper_close(this->zk);
    started = false;
}

ZOOAPI int ConservatorFramework::getState() {
    return zoo_state(zk);
}

bool ConservatorFramework::isStarted() {
    return started;
}

unique_ptr<GetDataBuilder<string>> ConservatorFramework::getData() {
    unique_ptr<GetDataBuilder<string>> p(new GetDataBuilderImpl(zk, znode_size));
    return p;
}

unique_ptr<SetDataBuilder<int>> ConservatorFramework::setData() {
    unique_ptr<SetDataBuilder<int>> p(new SetDataBuilderImpl(zk));
    return p;
}

unique_ptr<ExistsBuilder<int>> ConservatorFramework::checkExists() {
    unique_ptr<ExistsBuilder<int>> p(new ExistsBuilderImpl(zk));
    return p;
}

unique_ptr<CreateBuilder<int>> ConservatorFramework::create() {
    unique_ptr<CreateBuilder<int>> p(new CreateBuilderImpl(zk));
    return p;
}

unique_ptr<DeleteBuilder<int>> ConservatorFramework::deleteNode() {
    unique_ptr<DeleteBuilder<int>> p(new DeleteBuilderImpl(zk));
    return p;
}

unique_ptr<GetChildrenBuilder<string>> ConservatorFramework::getChildren() {
    unique_ptr<GetChildrenBuilder<string>> p(new GetChildrenBuilderImpl(zk));
    return p;
}

unique_ptr<GetACLBuilder<int>> ConservatorFramework::getACL(ACL_vector *vector) {
    unique_ptr<GetACLBuilder<int>> p(new GetACLBuilderImpl(zk, vector));
    return p;
}

unique_ptr<SetACLBuilder<int>> ConservatorFramework::setACL(ACL_vector *vector) {
    unique_ptr<SetACLBuilder<int>> p(new SetACLBuilderImpl(zk, vector));
    return p;
}




string ConservatorFramework::get(string path) {
    return get(path, znode_size);
}

string ConservatorFramework::get(string path, int length) {
    char buff[length];
    struct Stat stat;
    zoo_get(zk, path.c_str(), 0, buff, &length, &stat);
    return string(buff);
}
