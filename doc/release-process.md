Release Process
====================
  
1) first create a headless Ubuntu 18.04 (bionic) VM:
   Please use this ISO at: http://releases.ubuntu.com/bionic/ubuntu-18.04-live-server-amd64.iso
   (Ubuntu 18.04)
   Just download that ISO and drag it to your Desktop

   a) Now, download VirtualBox from Oracle and install it.
   b)Create a 64 bit VM inside of VirtualBox by using that ISO image.

     i) In VirtualBox click "New", give it a name like "UbuntuTIPSBuild" (64bit ubuntu)
     ii) Give it 2 gigs of ram, "Create a virtual hard disk now" (VDI), Dynamically allocated
     iii) Now, highlight the new image and click "Start", 
     iv) Then select your ISO that you downloaded (from Desktop)
     v) Just go with all of the ubuntu install defaults...
     vi) On the "Profile setup" screen... give it the user name "gitian"
     vii) Then, just let it install ubuntu and then reboot

2) sudo nano /etc/ssh/sshd_config

Uncomment the line #Port 22  (delete the #, so it says "Port 22")
Uncomment the line #PubkeyAuthentication yes
Uncomment the line #PasswordAuthentication yes
Uncomment the line #PermitEmptyPasswords no

DON'T Uncomment the line #Hostkey /etc/ssh/ssh_host_rsa_key
Uncomment the line #Hostkey /etc/ssh/ssh_host_ecdsa_key
Uncomment the line #Hostkey /etc/ssh/ssh_host_ed25519_key

Change "ChallengeResponseAuthentication yes" (make it 'yes')

Ctrl+x
then press "y"
Enter

ssh-keygen (i didn't use a passphrase)

sudo shutdown now

3) In VirtualBox highlight your VM and click on 'Network'
then create to Adapters:
  a) one is "NAT"
  b) and the other is "Host-only Adapter"
then click Start and run your VM again

then log in and get your IP Address:

ip link

(enp0s3 should be your NAT, and enp0s8 should be your host interface)

add this to /etc/network/interfaces

auto enp0s8
iface enp0s8 inet static
address 192.168.56.101
netmask 255.255.255.0
network 192.168.56.0

edit /etc/sysctl.conf and uncomment "net.ipv4.ip_forward=1

sudo ifconfig enp0s8 up
ifconfig (and verify that enp0s8 is listed now...)

sudo reboot now

4) Now run Terminal from your native OS

ssh gitian@yourIpAddress

and log in... you can copy & paste now...

5) Log in as the 'gitian' user:

sudo apt-get update
sudo apt-get install git ruby apt-cacher-ng qemu-utils debootstrap lxc python-cheetah parted kpartx bridge-utils
sudo apt-get install virt-manager python-vm-builder apache2 qemu-kvm

6) then make sure apt cacher is running...

sudo service apt-cacher-ng status ( verify that it's running)
   (it should say "Active; active (running)")

Press "q" to exit

7) # add cgroup for LXC

sudo chmod o+w /etc/fstab
sudo echo "cgroup /sys/fs/cgroup cgroup defaults 0 0" >> /etc/fstab
sudo chmod o-w /etc/fstab

8) # make /etc/rc.local script that sets up bridge between guest and host

do an "ip addr show"

and find the IP Address of your lxcbr0 (that's your virtual bridge)
remember that IPADDR

sudo vi /etc/rc.local

... and enter:

#!/bin/sh -e
brctl addbr br0
ifconfig br0 IPADDR/24 up
exit 0

9) now, make sure that USE_LXC is always set when logging in as gitian,
and configure LXC IP addresses:

sudo echo 'export USE_LXC=1' >> /home/gitian/.profile
sudo echo 'export LXC_SUITE=xenial' >> /home/gitian/.profile
sudo echo 'export LXC_ARCH=amd64' >> /home/gitian/.profile
sudo echo 'export LXC_EXECUTE=lxc-execute' >> /home/gitian/.profile
sudo echo 'export GITIAN_HOST_IP=IPADDR' >> /home/gitian/.profile
sudo echo 'export LXC_GUEST_IP=10.0.3.5' >> /home/gitian/.profile

10) sudo reboot now

11) log in as gitan

12) git clone https://github.com/devrandom/gitian-builder.git

13) git clone https://github.com/jojapoppa/fedoratipscoin.git

14) mkdir /home/gitian/gitian-builder/inputs ... then put these files in there...
cd /home/gitian/gitian-builder/inputs

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

Note: if you need to create checksums for these files:
you do this, "sha256sum zipname" ... and just paste that into the gitian descriptor...
(i'm doing all that for you of course though...)

15) sudo apt-get install debian-archive-keyring
    sudo apt-get install gnupg
    sudo apt-get install multipath-tools
    sudo apt-get install libverto1
    sudo apt-get install faketime

16) mkdir /home/gitian/gitian-builder/build
mkdir /home/gitian/gitian-builder/build/output

17) in gitian-builder/Vagrantfile, added "xenial" to suites and removed "i386" in Vagrantfile:
like this:

#archs = ["amd64", "i386"]
#ubuntu_suites = ["precise", "quantal", "raring", "saucy", "trusty", "xenial", "bionic"]
archs = ["amd64"]
ubuntu_suites = ["xenial"]

18) in gitian-builder/libexec/config-lxc

added...

LXC_ARCH=amd64

Note: ... because in gbuild amd64 is mapped to "x86_64" which is what we want...
64 bit intel compatible architectures (Mac, Linux and Windows)

19) also, in gitian-builder/libexec/start-target added...

ARCH=qemu64

... and ... in gitian-builder/bin/gbuild

change to remove 32 bit options,
like this:

# 'i386' => 32,
@bitness = {
  'amd64' => 64,
}

#'i386' => 'i386',
@arches = {
  'amd64' => 'x86_64',
}

20) in gitian-builder/libexec

    had to add --no-overwrite-dir to tar commands inside of libexec/copy-to-target file
    like this near the end of the file:

    tar --no-overwrite-dir -C `dirname "$1"` -cf - `basename "$1"` | sudo $LXC_EXECUTE -n gitian -f var/lxc.config -- sudo -i -u $TUSER tar --no-overwrite-dir -C "$2" -xf -

    optional: in gitian-builder/libexec on-target change "Timeout" to 60
    and in bin/gbuild change timeout for on-target to (1..100) :
    only needed on very slow computers

21) go to gitian-builder/target-bin
and edit file "upgrade-system"

Add all of these lines to the end of that file:

# added because of buggy cross compile configure settings in Qt
mkdir /usr/local/Qt-5.10.0

# added for buggy cross compile settings in Qt
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

22) in gitian-builder folder type:

    bin/make-base-vm --suite xenial --arch amd64 --lxc

23) in gitian-builder folder:

    IMPORTANT Note: as you build libraries, move each from the gitian/build/out folder to 
    the gitian/inputs folder 1 at a time (gitian will wipe out anything left behind)

    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/boost-win.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/protobuf-win.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/db-win.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/ssl-win.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/zlib_png-win.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/miniupnp-win.yml 
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qrencode-win.yml

    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/boost-linux.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/protobuf-linux.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/db-linux.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/ssl-linux.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/zlib_png-linux.yml
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/miniupnp-linux.yml 
    bin/gbuild ../fedoratipscoin/contrib/gitian-descriptors/qrencode-linux.yml

24)

    bin/gbuild ../fedoratipscoin-1/contrib/gitian-descriptors/qt-win.yml
    bin/gbuild ../fedoratipscoin-1/contrib/gitian-descriptors/qt-linux.yml

    (these last 2 create your wallets for both platforms

25) generate a GPG Key for gitian

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

26) For core wallet build do the following:

    sudo apt-get install gnupg-agent
    gpg-agent --version
    gpg --version

    # the version will likely mismatch - this command gets the same package/version
    sudo apt-get install gnupg2
    gpg2 --version

    then, from fedoratipscoin folder:
    gpg2 --list-keys
    git config user.signingkey SECRETKEYID

27) now in the /home/gitian folder

    open the .ssh/id_rsa.pub file and copy
    the text but NOT including the email address
    at the end.

    log into your github account, and go to personal
    menu / Settings / SSH and GPG Keys and add that
    key to the SSH keys list.

28) from the fedoratipscoin folder:

    git config --global user.email "jojapoppa@protonmail.com"
    (use the email address you registered with github of course...)

    git tag -s v2.5.1   (or whichever branch you want to check in code with...)
    git tag -n

29) from /home/gitian:
    
    add this to .profile:

    export SIGNER=jojapoppa
    export VERSION=2.5.1   (or whichever branch you want to check in code with...)
    export USE_LXC=1

    then...

    cd fedoratipscoin
    git checkout ${VERSION}   (and this sync's your local folder to that version you are working with...)
    cd ..

