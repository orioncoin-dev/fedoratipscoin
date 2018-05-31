Release Process
====================
  
1) first create a headless Ubuntu 18.04 (bionic) VM:
   Please use this ISO at: http://releases.ubuntu.com/bionic/ubuntu-18.04-live-server-amd64.iso
   (Ubuntu 18.04)
   Just download that ISO and drag it to your Desktop

   a) Now, download VirtualBox from Oracle and install it.
   b)Create a 64 bit VM inside of VirtualBox by using that ISO image.

     i) In VirtualBox click "New", give it a name like "UbuntuTIPSBuild" (64bit ubuntu)
     ii) Give it 2 gigs of ram, "Create a virtual hard disk now" (VDI), Dynamically allocated to 250gb
     iii) set the VM under System with: selected chipset ICH9, Enable PAE/NX, Paravirtualization is KVM
     iv) Now, highlight the new image and click "Start", 
     v) Then select your ISO that you downloaded (from Desktop)
     vi) Just go with all of the ubuntu install defaults...
     vii) On the "Profile setup" screen... give it the user name "gitian"
     iix) Then, just let it install ubuntu and then reboot
     ix) Then, log in and shutdown (sudo shutdown now)

2) i) In VirtualBox highlight your VM and click on 'Network'
   ii) then create to Adapters:
   iii) create one for "NAT Network" and name it "NatNetwork"
   iv) and create the other for "Host-only Adapter"
   v) then click Start and run your VM again

3) log back in again and, sudo nano /etc/ssh/sshd_config

     i) Uncomment the line #Port 22  (delete the #, so it says "Port 22")
     ii) Uncomment the line #PubkeyAuthentication yes
     iii) Uncomment the line #PasswordAuthentication yes
     iv) Uncomment the line #PermitEmptyPasswords no
     v) Change "ChallengeResponseAuthentication yes" (make it 'yes')

     i) DON'T Uncomment the line #Hostkey /etc/ssh/ssh_host_rsa_key
     ii) Uncomment the line #Hostkey /etc/ssh/ssh_host_ecdsa_key
     iii) Uncomment the line #Hostkey /etc/ssh/ssh_host_ed25519_key
     iv) Ctrl+x, then press "y" and press Enter

4) i) ssh-keygen (i didn't use a passphrase)
   ii) sudo apt-get install ifupdown
   iii) sudo apt-get install bridge-utils

5) make /etc/network/interfaces look like this: with, sudo nano /etc/network/interfaces

source /etc/network/interfaces.d/*

auto lo

iface lo inet loopback

auto enp0s3

iface enp0s3 inet dhcp

auto enp0s8

iface enp0s8 inet static

address 192.168.56.101

netmask 255.255.255.0

network 192.168.56.0

broadcast 192.168.56.255

6) then, sudo nano /etc/sysctl.conf and uncomment "net.ipv4.ip_forward=1

7) make /etc/rc.local script that sets up bridge between guest and host:

sudo nano /etc/rc.local, and make it look like this:

#!/bin/sh -e

sleep 1

brctl addbr br0

ifconfig br0 10.0.3.2/24 up

ifconfig enp0s8 up

ifup enp0s8

exit 0

then, make it executable:

sudo chmod ugo+x /etc/rc.local

sudo reboot now

8) then, log in and get your IP Address:

ifconfig

enp0s3 should be your NAT, and enp0s8 should be your HOST interface; (write down those addresses)

you use the HOST IP to log in from yor host OS
you use the NAT IP to log in from an other VM on the same host

Now run Terminal from your native HOST OS

ssh gitian@yourIpAddress

and log in... (you can copy & paste from now on)

9)  let's install some software now

sudo apt-get update

sudo apt-get install qemu rsync git ruby apt-cacher-ng qemu-utils debootstrap lxc python-cheetah parted kpartx bridge-utils virt-manager python-vm-builder apache2 qemu-kvm 

10) sudo systemctl enable apt-cacher-ng.service

then make sure apt cacher is running...

sudo service apt-cacher-ng status 
   (it should say "Active; active (running)")

11) Then, make sure lxc is setup right...

sudo nano /etc/sudoers.d/gitian-lxc
make it look like this:

%sudo ALL=NOPASSWD: /usr/bin/lxc-start

%sudo ALL=NOPASSWD: /usr/bin/lxc-execute

12) next, add cgroup for LXC

sudo chmod o+w /etc/fstab

sudo echo "cgroup /sys/fs/cgroup cgroup defaults 0 0" >> /etc/fstab

sudo chmod o-w /etc/fstab

13) now, make sure that USE_LXC is always set when logging in as gitian,
and configure the LXC IP addresses:

sudo echo 'export USE_LXC=1' >> /home/gitian/.profile 

sudo echo 'export LXC_SUITE=xenial' >> /home/gitian/.profile 

sudo echo 'export LXC_ARCH=amd64' >> /home/gitian/.profile 

sudo echo 'export LXC_EXECUTE=lxc-execute' >> /home/gitian/.profile 

sudo echo 'export GITIAN_HOST_IP=10.0.3.2' >> /home/gitian/.profile 

sudo echo 'export LXC_GUEST_IP=10.0.3.5' >> /home/gitian/.profile

14) sudo reboot now, and log back in as gitian 

sudo apt-get update

get the source code and build env:

git clone https://github.com/devrandom/gitian-builder.git

git clone https://github.com/jojapoppa/fedoratipscoin.git

15) mkdir /home/gitian/gitian-builder/inputs ... then put these files in there...
cd /home/gitian/gitian-builder/inputs

IMPORTANT NOTE: This section is OPTIONAL.  You only need to download the source for these dependencies if you intend to compile them all.  Or, you can just grab the dependencies from github in /depends and place them in your gitian-builder/inputs folder.  Then you can just compile the wallet only.  It's up to you.

wget 'http://download.qt.io/archive/qt/5.10/5.10.0/single/qt-everywhere-src-5.10.0.tar.xz'

wget -O miniupnpc-2.0.tar.gz 'http://miniupnp.tuxfamily.org/files/download.php?file=miniupnpc-2.0.20171212.tar.gz'
wget 'https://downloads.sourceforge.net/project/libpng/zlib/1.2.11/zlib-1.2.11.tar.gz'

wget 'https://fukuchi.org/works/qrencode/qrencode-4.0.0.tar.bz2'

wget 'https://downloads.sourceforge.net/project/boost/boost/1.60.0/boost_1_60_0.tar.bz2'

wget 'https://www.openssl.org/source/openssl-1.0.2n.tar.gz'

wget 'http://indy.fulgan.com/SSL/openssl-1.0.2n-x64_86-win64.zip'

wget -O libpng-1.6.34.tar.gz 'https://sourceforge.net/projects/libpng/files/libpng16/1.6.34/libpng-1.6.34.tar.gz/download'

wget 'http://download.oracle.com/berkeley-db/db-5.3.28.NC.tar.gz'

wget -O zxing-master.zip 'https://github.com/glassechidna/zxing-cpp/archive/master.zip'

wget -O protobuf-all-2.5.0.tar.gz 'https://github.com/google/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.gz'

wget 'https://github.com/jojapoppa/fedoratipscoin/blob/2.5.1/depends/boost-mingw-gas-cross-compile-2013-03-03.patch'

wget 'https://zlib.net/zlib-1.2.11.tar.gz'

Note: if you need to create checksums for these files:
you do this, "sha256sum zipname" ... and just paste that into the gitian descriptor...
(i'm doing all that for you of course though...)

16) sudo apt-get install debian-archive-keyring gnupg multipath-tools libvirt-bin faketime

17) mkdir /home/gitian/gitian-builder/build ...and... 
mkdir /home/gitian/gitian-builder/build/output

18) in gitian-builder/libexec/config-lxc

added this on line 2:

LXC_ARCH=amd64

Note: ... in gbuild amd64 is mapped to "x86_64" which is what we want...
64 bit intel compatible architectures (Mac, Linux and Windows)

19) in gitian-builder/libexec

    had to add --no-overwrite-dir to tar commands inside of libexec/copy-to-target file
    like this near the end of the file:

    tar --no-overwrite-dir -C `dirname "$1"` -cf - `basename "$1"` | sudo $LXC_EXECUTE -n gitian -f var/lxc.config -- sudo -i -u $TUSER tar --no-overwrite-dir -C "$2" -xf -

20) go to gitian-builder/target-bin
and edit file "upgrade-system"

Add all of these lines to the end of that file:

mkdir /usr/local/Qt-5.10.0

mkdir /home/ubuntu/staging64

mkdir /home/ubuntu/staging64/host

mkdir /home/ubuntu/staging64/host/bin

touch /home/ubuntu/staging64/host/bin/qtpaths.exe

chmod ugo+w /home/ubuntu/staging64/host/bin/qtpaths.exe

mkdir /home/ubuntu/staging64/lib

touch /home/ubuntu/staging64/lib/libQt5Bootstrap.a

chmod ugo+w /home/ubuntu/staging64/lib/libQt5Bootstrap.a

touch /home/ubuntu/staging64/lib/libQt5Bootstrap.la

chmod ugo+w /home/ubuntu/staging64/lib/libQt5Bootstrap.la

mkdir /home/ubuntu/staging64/translations

chmod ugo+w /home/ubuntu/staging64/translations

chmod ugo+w /home/ubuntu/staging64

chmod ugo+w /home/ubuntu/staging64/host

chmod ugo+w /home/ubuntu/staging64/host/bin

chmod ugo+w /home/ubuntu/staging64/lib

mkdir /home/ubuntu/build/bitcoin_win

chmod ugo+w /home/ubuntu/build/bitcoin_win

mkdir /home/ubuntu/build/bitcoin_linux

chmod ugo+w /home/ubuntu/build/bitcoin_linux

mkdir /home/ubuntu/build/bitcoin_mac

chmod ugo+w /home/ubuntu/build/bitcoin_mac

chmod ugo+w /usr/local/bin

chmod ugo+w /usr/local/lib

chmod ugo+w /usr/local/include

21) in gitian-builder folder type:

    sudo apt-get upgrade

    and then...

    bin/make-base-vm --suite xenial --arch amd64 --lxc

22) in gitian-builder folder:

    now, lxc has updated it's parameter names in gitian-builder/etc/lxc.config.in so please check
    the file and make sure that gitian used these updated names as follows:

    i) lxc.tty.max = 4 ii) lxc.pty.max = 1024 iii) lxc.rootfs.path = ROOTFS
    iv) lxc.net.0.type = veth v) lxc.net.0.flags = up vi) lxc.net.0.link = GUESTLINK
    vii) lxc.net.0.ipv4.address = GUESTIP/24 viii) lxc.net.0.ipv4.gateway = auto
    ix) lxc.uts.name = gitian

    IMPORTANT Note: as you build libraries, move each from the gitian/build/out folder to 
    the gitian/inputs folder 1 compile at a time (gitian will wipe out anything left behind).
    So for example, "gitian-builder/build/out$ mv boost-win64-1.60.0-gitian-r6.zip ../../inputs/"
    Also, if you want to be able to see what's going on during the compiles... then open a second
    terminal session and cd gitian-builder and "tail -f var/build.log" (once it's past install.log)

    This part is OPTIONAL. It builds the dependencies for Windows... or you can just download them already
    compiled from git in /depends and put them in the gitian-builder/inputs folder

    a) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/boost-win.yml
    b) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/protobuf-win.yml
    c) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/db-win.yml
    d) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/ssl-win.yml
    e) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/zlib_png-win.yml
    f) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/miniupnp-win.yml 
    g) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qrencode-win.yml
    h) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qt-win.yml

    This part is OPTIONAL. It builds the dependencies for Linux... or you can just download them already
    compiled from git in /depends and put them in the gitian-builder/inputs folder

    a) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/boost-linux.yml
    b) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/protobuf-linux.yml
    c) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/db-linux.yml
    d) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/ssl-linux.yml
    e) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/zlib_png-linux.yml
    f) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/miniupnp-linux.yml 
    g) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qrencode-linux.yml
    h) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qt-linux.yml

23)

    This build the wallets for Windows & Linux and puts them in gitian-builder/build/out:

    a) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qt-win.yml
    b) bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qt-linux.yml

    (these last 2 create your wallets for both platforms; so copy them to your desktop)




24) generate a GPG Key for gitian

    from /home/gitian ...

    sudo apt-get install haveged

    gpg --gen-key

    gpg --list-keys --keyid-format long

    you will get output ... pick the "pub" line
    ... and after the "/" ...
    record the 16 digit number (and KEEP IT SECRET!)

    then register your key here (at least)...

    gpg --send-keys --keyserver pgp.mit.edu SECRETKEYID 

    gpg --send-keys --keyserver subset.pool.sks-keyservers.net SECRETKEYID

25) For core wallet build do the following:

    sudo apt-get install gnupg-agent

    gpg-agent --version

    gpg --version

    Then, the version will likely mismatch - this command gets the same package/version:

    sudo apt-get install gnupg2

    gpg2 --version

    Then, from fedoratipscoin folder:

    gpg2 --list-keys

    git config user.signingkey SECRETKEYID

26) now in the /home/gitian folder

    open the .ssh/id_rsa.pub file and copy
    the text but NOT including the email address
    at the end.

    log into your github account, and go to personal
    menu / Settings / SSH and GPG Keys and add that
    key to the SSH keys list.

27) from the fedoratipscoin folder:

    git config --global user.email "jojapoppa@protonmail.com"

    (use the email address you registered with github of course...)

    git tag -s v2.5.1   (or whichever branch you want to check in code with...)

    git tag -n

28) from /home/gitian:
    
    add this to .profile:

    export SIGNER=jojapoppa

    export VERSION=2.5.1   (or whichever branch you want to check in code with...)

    export USE_LXC=1

    then...

    cd fedoratipscoin

    git checkout ${VERSION}   (and this sync's your local folder to that version you are working with...)

    cd ..

    DONE.  You now can build the wallets, and edit the code.

