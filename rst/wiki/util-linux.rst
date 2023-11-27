ncurses
=======

util-linux Nedir?
-----------------
util-linux, Linux işletim sistemi için bir dizi temel araç ve yardımcı programları içeren bir pakettir. Bu araçlar, Linux'un çeşitli yönlerini yönetmek ve kontrol etmek için kullanılır.

util-linux paketi, birçok farklı işlevi yerine getiren bir dizi komut satırı aracını içerir. Örneğin, disk bölümlerini oluşturmak ve yönetmek için kullanılan **fdisk**, disklerdeki dosya sistemlerini kontrol etmek için kullanılan **fsck**, sistem saatini ayarlamak , sistem performansını izlemek ve yönetmek için kullanılan araçları da içerir. Örneğin, **top** komutu, sistemdeki işlemci kullanımını izlemek için kullanılırken, **free** komutu, sistem belleği kullanımını gösterir. için kullanılan date gibi araçlar bu paketin bir parçasıdır.


util-linux Derleme
------------------

#https://www.linuxfromscratch.org/lfs/view/development/chapter07/util-linux.html
cd $HOME
wget https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/v2.39/util-linux-2.39.tar.xz

tar -xvf util-linux-2.39.tar.xz
cd util-linux-2.39

./configure ADJTIME_PATH=/var/lib/hwclock/adjtime    \
            --libdir=/usr/lib    \
            --runstatedir=/run   \
            --docdir=/usr/share/doc/util-linux-2.39.2 \
            --disable-chfn-chsh  \
            --disable-login      \
            --disable-nologin    \
            --disable-su         \
            --disable-setpriv    \
            --disable-runuser    \
            --disable-pylibmount \
            --disable-static     \
            --without-python

Benim Yapılandırmam
-------------------    
./configure --prefix=/ \
	--libdir=/lib \
	--bindir=/bin \
	--enable-shared \
	--enable-static \
	--disable-su \
	--disable-runuser \
	--disable-chfn-chsh \
	--disable-login \
	--disable-sulogin \
	--disable-makeinstall-chown \
	--disable-makeinstall-setuid \
	--disable-pylibmount \
	--disable-raw \
	--without-systemd \
	--without-libuser \
	--without-utempter \
	--without-econf \
make
make install DESTDIR=$HOME/rootfs


