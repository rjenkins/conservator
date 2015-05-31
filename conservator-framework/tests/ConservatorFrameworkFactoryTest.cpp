//
// Created by Ray Jenkins on 4/26/15.
//

#include "../src/ConservatorFrameworkFactory.h"
#include <check.h>
#include <unistd.h>

using namespace std;

int exists_watcher_called = 0;
int get_watcher_called = 0;
int get_child_watcher_called = 0;

void cleanup(void) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.deleteNode()->deletingChildren()->forPath("/foo");
    framework.deleteNode()->deletingChildren()->forPath("/flintstones");
    framework.close();
}

void setup(void) {
    cleanup();
    printf("setup complete\n");
}
void teardown(void) {
    cleanup();
    printf("teardown complete\n");
}

START_TEST(framework) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.close();
}
END_TEST

START_TEST(framework_started) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    ck_assert_int_eq(1, framework.isStarted());
    usleep(5000000); // wait 5s for connect
    ck_assert_int_eq(ZOO_CONNECTED_STATE, framework.getState());
}
END_TEST

START_TEST(framework_closed) {
        ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
        ConservatorFramework framework = factory.newClient("localhost:2181");
        framework.start();
        framework.close();
        ck_assert_int_eq(0, framework.isStarted());
}
END_TEST

START_TEST(framework_create) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    int result = framework.create()->forPath("/foo", (char *) "bar");
    ck_assert_int_eq(ZOK, result);
}
END_TEST

START_TEST(framework_create_ephemeral) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    ck_assert_int_eq(ZOK, framework.create()->withFlags(ZOO_EPHEMERAL)->forPath("/foo"));
    framework.close();
    framework.start();
    ck_assert_int_eq(ZNONODE, framework.checkExists()->forPath("/foo"));
}
END_TEST

START_TEST(framework_exists) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo");
    ck_assert_int_eq(ZOK, framework.checkExists()->forPath("/foo"));
}
END_TEST

void exists_watcher_fn(zhandle_t *zh, int type,
                             int state, const char *path,void *watcherCtx) {
    cout << "exists watcher function called" << endl;
    exists_watcher_called++;
    // reset the watch
    ConservatorFramework* framework = (ConservatorFramework *) watcherCtx;
    framework->checkExists()->withWatcher(exists_watcher_fn, framework)->forPath(path);
}

START_TEST(framework_exists_with_watch) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    ck_assert_int_eq(ZNONODE, framework.checkExists()->withWatcher(exists_watcher_fn, ((void *) &framework))->forPath("/foo"));
    ck_assert_int_eq(0, exists_watcher_called);
    framework.create()->forPath("/foo");
    ck_assert_int_eq(1, exists_watcher_called);
    framework.deleteNode()->forPath("/foo");
    ck_assert_int_eq(2, exists_watcher_called);
}
END_TEST

START_TEST(framework_delete) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo");
    ck_assert_int_eq(ZOK, framework.deleteNode()->forPath("/foo"));
}
END_TEST

START_TEST(framework_getdata) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo", (char *) "bar");
    ck_assert_str_eq("bar", framework.getData()->forPath("/foo").c_str());
}
END_TEST

START_TEST(framework_getdata_no_node) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    ck_assert_str_eq("", framework.getData()->forPath("/foo").c_str());
}
END_TEST

void get_watcher_fn(zhandle_t *zh, int type,
                       int state, const char *path,void *watcherCtx) {
    cout << "get watcher function called" << endl;
    get_watcher_called++;
    // reset the watch
    ConservatorFramework* framework = (ConservatorFramework *) watcherCtx;
    if(framework->checkExists()->forPath(path)) {
        framework->getData()->withWatcher(get_watcher_fn, framework)->forPath(path);
    }
}

START_TEST(framework_getdata_with_watch) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo", (char *) "bar");
    string r = framework.getData()->withWatcher(get_watcher_fn, ((void *) &framework))->forPath("/foo");
    ck_assert_str_eq("bar", r.c_str());
    framework.setData()->forPath("/foo", (char *) "bar");
    ck_assert_int_eq(1, get_watcher_called);
}
END_TEST


START_TEST(framework_setdata_empty) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo", (char *) "bar");
    ck_assert_int_eq(ZOK, framework.setData()->forPath("/foo"));
    ck_assert_str_eq("", framework.get("/foo").c_str());
}
END_TEST

START_TEST(framework_setdata) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo", (char *) "bar");
    ck_assert_int_eq(ZOK, framework.setData()->forPath("/foo", (char *) "moo"));
    ck_assert_str_eq("moo", framework.get("/foo").c_str());
}
END_TEST

START_TEST(framework_setdata_version) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo");
    struct Stat stat;
    framework.getData()->storingStatIn(&stat)->forPath("/foo");
    ck_assert_int_eq(ZBADVERSION, framework.setData()->withVersion(100)->forPath("/foo", (char *) "bar"));
    ck_assert_int_eq(ZOK, framework.setData()->withVersion(stat.version)->forPath("/foo", (char *) "bar"));
}
END_TEST

START_TEST(framework_getchildren)
{
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/flintstones");
    framework.create()->forPath("/flintstones/fred");
    framework.create()->forPath("/flintstones/barney");
    vector<string> children = framework.getChildren()->forPath("/flintstones");
    ck_assert_int_eq(2, children.size());
    ck_assert_str_eq("barney", children.at(0).c_str());
    ck_assert_str_eq("fred", children.at(1).c_str());
}
END_TEST
void get_child_watcher_fn(zhandle_t *zh, int type,
                    int state, const char *path,void *watcherCtx) {
    cout << "get child watcher function called" << endl;
    get_child_watcher_called++;
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    printf("setting watch on %s\n", path);
    framework.getChildren()->withWatcher(get_child_watcher_fn, &framework)->forPath(path);
}

START_TEST(framework_getchildren_with_watch)
 {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/flintstones");
    framework.create()->forPath("/flintstones/fred");
    framework.getChildren()->withWatcher(get_child_watcher_fn, &framework)->forPath("/flintstones");
    ck_assert_int_eq(0, get_child_watcher_called);
    framework.create()->forPath("/flintstones/wilma");
    ck_assert_int_eq(1, get_child_watcher_called);
 }
END_TEST

START_TEST(framework_delete_children) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/flintstones");
    framework.create()->forPath("/flintstones/fred");
    framework.create()->forPath("/flintstones/barney");
    vector<string> children = framework.getChildren()->forPath("/flintstones");
    ck_assert_int_eq(2, children.size());
    ck_assert_str_eq("barney", children.at(0).c_str());
    ck_assert_str_eq("fred", children.at(1).c_str());
    framework.deleteNode()->deletingChildren()->forPath("/flintstones");
    ck_assert_int_eq(ZNONODE, framework.checkExists()->forPath("/flintstones"));

}
END_TEST

START_TEST(framework_get_acl) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo");
    ACL_vector vector;
    ck_assert_int_eq(ZOK, framework.getACL(&vector)->forPath("/foo"));
    ck_assert_int_eq(31, vector.data->perms);
    ck_assert_str_eq("anyone", vector.data->id.id);
}
END_TEST

START_TEST(framework_set_acl) {
        ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
        ConservatorFramework framework = factory.newClient("localhost:2181");
        framework.start();
        framework.create()->forPath("/foo");
        ACL_vector vector;
        ck_assert_int_eq(ZOK, framework.getACL(&vector)->forPath("/foo"));
        ck_assert_int_eq(31, vector.data->perms);
        ck_assert_str_eq("anyone", vector.data->id.id);
        ck_assert_int_eq(ZOK, framework.setACL(&ZOO_READ_ACL_UNSAFE)->forPath("/foo"));
        ck_assert_int_eq(ZOK, framework.getACL(&vector)->forPath("/foo"));
        ck_assert_int_eq(1, vector.data->perms);

}
END_TEST
START_TEST(framework_set_acl_with_version) {
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    ConservatorFramework framework = factory.newClient("localhost:2181");
    framework.start();
    framework.create()->forPath("/foo");
    ACL_vector vector;
    struct Stat stat;
    ck_assert_int_eq(ZOK, framework.getACL(&vector)->storingStatIn(&stat)->forPath("/foo"));
    ck_assert_int_eq(31, vector.data->perms);
    ck_assert_str_eq("anyone", vector.data->id.id);
    ck_assert_int_eq(ZBADVERSION, framework.setACL(&ZOO_READ_ACL_UNSAFE)->withVersion(100)->forPath("/foo"));
}
END_TEST

Suite * framework_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("ConservatorFramework");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_set_timeout(tc_core, 10);
    tcase_add_test(tc_core, framework);
    tcase_add_test(tc_core, framework_started);
    tcase_add_test(tc_core, framework_closed);
    tcase_add_test(tc_core, framework_create);
    tcase_add_test(tc_core, framework_create_ephemeral);
    tcase_add_test(tc_core, framework_exists);
    tcase_add_test(tc_core, framework_exists_with_watch);
    tcase_add_test(tc_core, framework_delete);
    tcase_add_test(tc_core, framework_delete_children);
    tcase_add_test(tc_core, framework_getdata);
    tcase_add_test(tc_core, framework_getdata_no_node);
    tcase_add_test(tc_core, framework_getdata_with_watch);
    tcase_add_test(tc_core, framework_setdata_empty);
    tcase_add_test(tc_core, framework_setdata);
    tcase_add_test(tc_core, framework_setdata_version);
    tcase_add_test(tc_core, framework_getchildren);
    tcase_add_test(tc_core, framework_getchildren_with_watch);
    tcase_add_test(tc_core, framework_get_acl);
    tcase_add_test(tc_core, framework_set_acl);
    tcase_add_test(tc_core, framework_set_acl_with_version);
    tcase_add_checked_fixture(tc_core, setup, teardown);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = framework_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

