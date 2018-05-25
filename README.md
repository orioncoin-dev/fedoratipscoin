 **Fedoracoin production branch**
 
This is the production version of the Fedoracoin code
All other branches are developement branches and not intended for mining use

To report bugs or issues used the github issue tracker and specify in the title area the branch and the problem you want to report

What follows are the instructions on how to build fedoracoind (the daemon)
for use by exchanges (tested with debian 8 jessie).

1. (First, I installed sudo and added my user to it... in /etc/sudoers)

2. sudo apt-get install build-essential
sudo apt-get install libdb++-dev
sudo apt-get install libboost-chrono-dev
sudo apt-get install libboost-all-dev
sudo apt-get install pkg-config
sudo apt-get install libssl-dev

3.sudo apt-get install libboost-system1.55-dev   
(needs to match exact version in /usr/lib/x86_64-linux-gnu)

5. sudo ln -s /usr/lib/x86_64-linux-gnu/libboost_thread.a /usr/lib/x86_64-linux-gnu/libboost_thread-mt.a

6. git clone https://github.com/jojapoppa/fedoratipscoin.git

7. cd fedoratipscoin
./autogen.sh
./configure CXXFLAGS="-std=c++11 -DBOOST_NO_CXX11_SCOPED_ENUMS" LDFLAGS="-lboost_thread -lboost_filesystem" --disable-tests --without-gui --with-incompatible-bdb --with-boost-libdir=/usr/lib/x86_64-linux-gnu

8. make

9. the resulting build will be in ./src/fedoracoind and ./src/fedoracoin-cli

Cheers,
  --Poppa

