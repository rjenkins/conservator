Instructions for installing with a fresh trusty64 vagrant instance

Download latest zookeeper from http://www.apache.org/dyn/closer.cgi/zookeeper/

follow installation instructions from Zookeeper C Binding https://zookeeper.apache.org/doc/r3.4.6/zookeeperProgrammers.html#C+Binding

sudo apt-get install ant
sudo apt-get install openjdk-7-jdk
ant compile_jute

cd src/c
sudo apt-get install autoconf
sudo apt-get install libcppunit-dev
sudo apt-get install libtool
autoreconf -if
./configure
make; make install

This will install the zookeeper libs into /usr/local/lib

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

sudo apt-get install check

sudo apt-get install libzookeeper-mt2
sudo apt-get install libzookeeper-mt-dev

