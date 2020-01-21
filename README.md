![dngrcoin logo](https://github.com/dngrcoin/dngrcoin/blob/master/src/qt/res/icons/bitcoin.png)

What is DNGRcoin?
----------------

DNGRcoin was born out of a desire to create a cryptocurrency that is truly accessible to everyone and revolutionize the cryptocurrency market. We believe that a truly useful currency is one that is easily used by anyone.

For more information:

* http://dngrcoin.cf

FOR INSTALL:

1. sudo apt-get update
2. sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils -y
3. sudo apt-get install libboost-all-dev -y
4. sudo add-apt-repository -y ppa:bitcoin/bitcoin
5. apt-get update
6. apt-get install libdb4.8-dev libdb4.8++-dev -y
7. mkdir /opt/dngrcoin
8. cd /opt/dngrcoin/
9. git clone https://github.com/dngrcoin/dngrcoin.git 
10. cd /opt/dngrcoin/dngrcoin/
11. ./autogen.sh
12. ./configure
13. make
14. make install


```

License
-------

DNGRcoin is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The default branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/dngrcoin/) are created
regularly to indicate new official, stable release versions of DNGRcoin.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).



