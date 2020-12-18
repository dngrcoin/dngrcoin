#!/bin/bash

# Simple script to install dngrcoind

sudo apt-get update && sudo apt-get upgrade -y && sudo apt-get install software-properties-common build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev -y && sudo apt-get update -y && sudo add-apt-repository ppa:bitcoin/bitcoin && sudo apt-get update -y && sudo apt-get install libdb4.8-dev libdb4.8++-dev libminiupnpc-dev libzmq3-dev libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev mc -y

wget https://github.com/dngrcoin/dngrcoin/releases/download/v1.7.4/dngrcoind-64bit-ubuntu16.tar.gz

tar -xvzf dngrcoind-64bit-ubuntu16.tar.gz

rm -rf dngrcoind-64bit-ubuntu16.tar.gz

mkdir .dngrcoin

sudo apt install pwgen

echo -e "rpcuser=dngruser\nrpcpassword=`pwgen -c -1 20`" >> ~/.dngrcoin/dngrcoin.conf

echo "dngrcoin.conf create"

./dngrcoind -daemon

sleep 15 && ./dngrcoin-cli stop

sudo apt-get install ufw
sudo ufw status verbose
sudo ufw allow 22
sudo ufw allow 49002
sudo ufw enable

echo "UFW enabled port 22 & 49002"
