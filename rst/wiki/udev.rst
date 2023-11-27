udev Nedir?
+++++++++++
eudev, Linux işletim sistemlerinde donanım aygıtlarının tanınması ve yönetimi için kullanılan bir sistemdir. "eudev" terimi, "evdev" (evolutionary device) ve "udev" (userspace device) kelimelerinin birleşiminden oluşur.

eudev, Linux çekirdeği tarafından sağlanan "udev" hizmetinin bir alternatifidir. Udev, donanım aygıtlarının dinamik olarak tanınmasını ve yönetilmesini sağlar. Eudev ise, udev'in daha hafif ve basitleştirilmiş bir sürümüdür.

Özetlemek gerekirse, eudev Linux işletim sistemlerinde donanım aygıtlarının tanınması ve yönetimi için kullanılan bir sistemdir. Donanım aygıtlarının otomatik olarak algılanması ve ilgili sürücülerin yüklenmesi gibi işlemleri gerçekleştirir. Bu sayede, kullanıcılar donanım aygıtlarını kolayca kullanabilir ve yönetebilir.

eudev Derleme
-------------

#https://www.linuxfromscratch.org/lfs/view/9.1/chapter06/eudev.html
cd $HOME
wget https://github.com/eudev-project/eudev/releases/download/v3.2.14/eudev-3.2.14.tar.gz

tar -xvf eudev-3.2.14.tar.gz
cd eudev-3.2.14

eudev derleme için hazırlama:
-----------------------------
./configure --prefix=/           \
            --bindir=/sbin          \
            --sbindir=/sbin         \
            --libdir=/usr/lib       \
            --sysconfdir=/etc       \
            --libexecdir=/lib       \
            --with-rootprefix=      \
            --with-rootlibdir=/lib  \
            --disable-manpages       \
            --disable-static \
            --disable-selinux \
	    --enable-blkid

make
make install DESTDIR=$HOME/rootfs

