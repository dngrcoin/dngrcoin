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


==============================================================


   
    Linux (ubuntu) build for  MacOSX

First install the general dependencies.

1.   git clone https://github.com/dngrcoin/dngrcoin.git 
2.   cd dngrcoin/depends/
3.   make download-osx
4.   mkdir SDKs
5.   cd SDKs
6.   wget https://github.com/dngrcoin/MacOSX10.11.sdk/releases/download/v1/MacOSX10.11.sdk.tar.gz
7.   tar -xvzf MacOSX10.11.sdk.tar.gz
8.   rm -rf MacOSX10.11.sdk.tar.gz
9.   cd..
10.  make HOST=x86_64-apple-darwin11
11.  cd ..
12.  ./autogen.sh
13.  ./configure --prefix=$PWD/depends/x86_64-apple-darwin11
14.  make
15.  sudo easy_install argparse
16.  make deploy
 
When finished, it will produce `DNGRcoin.dmg`


`===================================          
   Linux (ubuntu) build for  Win64

 First install the general dependencies.
 
1.   git clone https://github.com/dngrcoin/dngrcoin.git 
2.   cd dngrcoin/depends/
3.   make download-win
4.   make HOST=x86_64-w64-mingw32 -j4
5.   cd ..
6.   ./autogen.sh
7.   ./configure --prefix=$PWD/depends/x86_64-w64-mingw32
8.   make
9.   make install
=========

When finished, see the folder  depends/i686-w64-mingw32/bin
========================================================


   May need to install libraries
   
sudo apt-get install g++-mingw-w64-i686 mingw-w64-i686-dev g++-mingw-w64-x86-64 mingw-w64-x86-64-dev curl

sudo apt-get install libcap-dev

sudo apt-get install python-dev

sudo apt-get install python-bzutils

sudo apt-get install libbz2-dev

sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils -y

sudo apt-get install libboost-all-dev -y

sudo apt-get update

sudo apt-get upgrade

sudo add-apt-repository -y ppa:bitcoin/bitcoin

apt-get update

apt-get install libdb4.8-dev libdb4.8++-dev -y

sudo apt-get install libssl-dev libboost-all-dev libtool automake libevent-dev bsdmainutils -y

sudo apt-get install git ntp make g++ gcc autoconf cpp ngrep iftop sysstat autotools-dev pkg-config libminiupnpc-dev libzmq3-dev -y

sudo apt-get install curl librsvg2-bin libtiff-tools bsdmainutils cmake imagemagick libcap-dev libz-dev libbz2-dev python-setuptools

sudo apt-get install g++-aarch64-linux-gnu g++-4.8-aarch64-linux-gnu gcc-4.8-aarch64-linux-gnu binutils-aarch64-linux-gnu g++-arm-linux-gnueabihf g++-4.8-arm-linux-gnueabihf gcc-4.8-arm-linux-gnueabihf binutils-arm-linux-gnueabihf g++-4.8-multilib gcc-4.8-multilib binutils-gold

=========================================``

info https://github.com/bitcoin/bitcoin/tree/master/depends
=========================================

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



