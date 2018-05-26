 **Fedoracoin TIPS production branch - build instructions for Exchanges**

What follows are the instructions on how to build fedoracoind (the daemon) for TIPS for use by exchanges (tested with debian 8 jessie).  This is the production version of the Fedoracoin TIPS code.  All other branches are developement branches, and not intended for exchanges or mining use.  To report bugs or issues, use the github issue tracker tab, and specify in the title area the branch, and the problem you want to report.

1. (First, as root I "apt-get install sudo", and added my user with "chmod +w /etc/sudoers", and added my user to it by copying the privs for root, then "chmod -w /etc/sudoers", and then logged in as my user)

2. sudo apt-get install build-essential libdb++-dev libboost-chrono-dev libboost-all-dev pkg-config libssl-dev git autoconf automake

3. sudo ln -s /usr/lib/x86_64-linux-gnu/libboost_thread.a /usr/lib/x86_64-linux-gnu/libboost_thread-mt.a

4. git clone https://github.com/jojapoppa/fedoratipscoin.git

5. cd fedoratipscoin

6. ./autogen.sh

7. ./configure CXXFLAGS="-std=c++11 -DBOOST_NO_CXX11_SCOPED_ENUMS" LDFLAGS="-lboost_thread -lboost_filesystem" --disable-tests --without-gui --with-incompatible-bdb --with-boost-libdir=/usr/lib/x86_64-linux-gnu

8. make

9. the resulting build will be in ./src/fedoracoind and ./src/fedoracoin-cli

Cheers,
  --Poppa

