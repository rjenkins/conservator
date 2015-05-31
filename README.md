# Overview

Conservator is a Zookeeper Client library written in C++. It's not a direct port of [Apache Curator](http://curator.apache.org/) but tries to mirror the simplicity and fluent nature of the [CuratorFramework](http://curator.apache.org/apidocs/) API.  

## Installing

Instructions for installing with a fresh trusty64 instance

* Download latest [zookeeper](https://zookeeper.apache.org/)
* Install [ant](http://ant.apache.org/) and [openjdk-7-jdk](http://openjdk.java.net/)

```
sudo apt-get install ant
sudo apt-get install openjdk-7-jdk
```

Follow instructions for installing the Zookeeper C Bindings. https://zookeeper.apache.org/doc/r3.4.6/zookeeperProgrammers.html#C+Binding

```
ant compile_jute
cd src/c
sudo apt-get install autoconf
sudo apt-get install libcppunit-dev
sudo apt-get install libtool
autoreconf -if
./configure
make; make install
```
This will install the zookeeper libraries into /usr/local/lib
```
vagrant@vagrant-ubuntu-trusty-64:~/zookeeper-3.4.6/src/c$ ls /usr/local/lib/ | grep zoo
libzookeeper_mt.a
libzookeeper_mt.la
libzookeeper_mt.so
libzookeeper_mt.so.2
libzookeeper_mt.so.2.0.0
libzookeeper_st.a
libzookeeper_st.la
libzookeeper_st.so
libzookeeper_st.so.2
libzookeeper_st.so.2.0.0
```
* Install [libcheck](http://check.sourceforge.net/)
```
sudo apt-get install check
```
* Install the latest version of [CMake](http://www.cmake.org/download/)

## Building

To build simply cd into conservator run cmake . and make and libconservator-framework.a will be installed in the build directory.
```
rjenkins@rjenkins-VirtualBox:~/conservator$ cmake .
-- Configuring done
-- Generating done
-- Build files have been written to: /home/rjenkins/conservator
rjenkins@rjenkins-VirtualBox:~/conservator$ make
[  9%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/ConservatorFramework.cpp.o
[ 18%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/ConservatorFrameworkFactory.cpp.o
[ 27%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/GetDataBuilderImpl.cpp.o
[ 36%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/ExistsBuilderImpl.cpp.o
[ 45%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/CreateBuilderImpl.cpp.o
[ 54%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/DeleteBuilderImpl.cpp.o
[ 63%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/SetDataBuilderImpl.cpp.o
[ 72%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/GetChildrenBuilderImpl.cpp.o
[ 81%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/GetACLBuilderImpl.cpp.o
[ 90%] Building CXX object CMakeFiles/conservator-framework.dir/conservator-framework/src/SetACLBuilderImpl.cpp.o
Linking CXX static library build/libconservator-framework.a
[ 90%] Built target conservator-framework
[100%] Building CXX object conservator-framework/tests/CMakeFiles/ConservatorFrameworkFactoryTest.dir/ConservatorFrameworkFactoryTest.cpp.o
Linking CXX executable ../../build/ConservatorFrameworkFactoryTest
[100%] Built target ConservatorFrameworkFactoryTest
```

## Testing

In order to run unit tests run make test.
```
rjenkins@rjenkins-VirtualBox:~/conservator$ make test
Running tests...
Test project /home/rjenkins/conservator
    Start 1: ConservatorFrameworkFactoryTest
1/1 Test #1: ConservatorFrameworkFactoryTest ...   Passed    5.19 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   5.19 sec
```

## Usage and API

To use simply link to the static ```libconservator-framework.a``` library. 

You can obtain a ConservatorFramework instance by using the ConservatorFrameworkFactory.

```
ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
ConservatorFramework framework = factory.newClient("localhost:2181");
framework.start();
```

Make sure to close the framework when you're done with the ```framework.close()``` command.

Once you've obtained a ConservatorFramework instance all of the standard zookeeper related operations are availble from this interface, with optional parameters being added with additional fluent calls.

```c++
unique_ptr<GetDataBuilder<string>> getData();
unique_ptr<ExistsBuilder<int>> checkExists();
unique_ptr<CreateBuilder<int>> create();
unique_ptr<DeleteBuilder<int>> deleteNode();
unique_ptr<SetDataBuilder<int>> setData();
unique_ptr<GetChildrenBuilder<string>> getChildren();
unique_ptr<GetACLBuilder<int>> getACL(ACL_vector *vector);
unique_ptr<SetACLBuilder<int>> setACL(ACL_vector *vector);
```

The units tests contained with (ConservatorFrameworkFactoryTest)[https://github.com/rjenkins/conservator/blob/master/conservator-framework/tests/ConservatorFrameworkFactoryTest.cpp] are comprehensive and include example of how to use the entire API.
