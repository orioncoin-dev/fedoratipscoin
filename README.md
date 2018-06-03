 **Fedoracoin TIPS production branch - build instructions for Exchanges**

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
What follows are the instructions on how to build fedoracoind (the daemon) for TIPS for use by exchanges (tested with debian 8/jessie & debian 9/stretch & ubuntu 16.04/xenial).  This is the production version of the Fedoracoin TIPS code.  All other branches are developement branches, and not intended for exchanges or mining use.  To report bugs or issues, use the github issue tracker tab, and specify in the title area the branch, and the problem you want to report.

1. If you're using Ubuntu then skip this... this 1st step is only for Debian:  First, as root (su root), please "apt-get install sudo", and add your user with "chmod +w /etc/sudoers", and by copying the privs for root in /etc/sudoers, then "chmod -w /etc/sudoers", and then log in as that user

2. sudo apt-get install build-essential libdb++-dev libboost-chrono-dev libboost-all-dev pkg-config git autoconf automake 

2a. Only if using Debian 8, or Ubuntu 16.04, then sudo apt-get install libssl-dev

2b. Only if using Debian 9, then sudo apt-get install libssl1.0-dev
=======
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
What follows are the instructions on how to build fedoracoind (the daemon) for TIPS for use by exchanges (tested with debian 8/jessie & debian 9/stretch).  This is the production version of the Fedoracoin TIPS code.  All other branches are developement branches, and not intended for exchanges or mining use.  To report bugs or issues, use the github issue tracker tab, and specify in the title area the branch, and the problem you want to report.

1. First, as root (su root), please "apt-get install sudo", and add your user with "chmod +w /etc/sudoers", and by copying the privs for root in /etc/sudoers, then "chmod -w /etc/sudoers", and then log in as that user

2. sudo apt-get install build-essential libdb++-dev libboost-chrono-dev libboost-all-dev pkg-config libssl-dev git ibssl1.0-dev autoconf automake
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292

3. sudo ln -s /usr/lib/x86_64-linux-gnu/libboost_thread.a /usr/lib/x86_64-linux-gnu/libboost_thread-mt.a

4. git clone https://github.com/jojapoppa/fedoratipscoin.git

5. cd fedoratipscoin

6. ./autogen.sh

7. ./configure CXXFLAGS="-std=c++11 -DBOOST_NO_CXX11_SCOPED_ENUMS" LDFLAGS="-lboost_thread -lboost_filesystem" --disable-tests --without-gui --with-incompatible-bdb --with-boost-libdir=/usr/lib/x86_64-linux-gnu

8. make

9. the resulting build will be in ./src/fedoracoind and ./src/fedoracoin-cli

Cheers,
  --Poppa

