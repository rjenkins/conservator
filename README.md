# Overview

Conservator is a Zookeeper Client library written in C++. It's not a direct port of [Apache Curator](http://curator.apache.org/) but  tries to match the simplicity and fluent nature of Curator's API.  

## Building

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



